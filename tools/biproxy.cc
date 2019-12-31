#include <arpa/inet.h>
#include <crypt.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <map>
#include <fstream>

unsigned char key[16];

void error(const char *msg) {
  perror(msg);
  exit(0);
}

void merror(const char *msg) {
  fputs(msg, stdout);
  putc('\n', stdout);
  exit(0);
}

int open_port(unsigned short port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("opening socket");
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  int retcode;
  retcode = inet_aton("3.93.128.89", &addr.sin_addr);
  if (!retcode) merror("cannot convert ip address");
  retcode = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (retcode) error("failed to connect to 12022");
  return sockfd;
}

// label should be at least 10 chars less than RECORD_SIZE:
#define RECORD_SIZE 40
void record(int readfd, int writefd, int transcriptfd, int rawfd, const std::string& cipher, const char *label) {
  int idx = 0;
  int total_idx = 0;
  // read from readfd, copy it to writefd, but also
  // copy a human readable form to transcriptfd
  // that copy has header line (the label),
  // hex-printed line, and a printable-chars line.
  while (1) {
    unsigned char buf[RECORD_SIZE];
    unsigned char partial_decrypted_buf[RECORD_SIZE];
    unsigned char decrypted_buf[RECORD_SIZE];
    ssize_t sz = read(readfd, buf, sizeof(buf));
    if (sz == -1) perror(label);
    if (sz == 0) {
      std::cerr << label << ": connection terminated." << std::endl;
      exit(0);
    }

    // Decrypt
    for (int i = 0; i < sz; ++i) {
      partial_decrypted_buf[i] = buf[i] ^ key[idx++];
	  if (total_idx < cipher.size()) {
		  decrypted_buf[i] = partial_decrypted_buf[i] ^ cipher[total_idx];
	  } else {
		  decrypted_buf[i] = partial_decrypted_buf[i];
	  }
	  total_idx++;
      if (idx >= 16) idx = 0;
    }

    // copy buf to the transcriptfd.  Do this atomically since
    // there's another process writing to it concurrently.  The
    // easiest way to do it concurrently is let the kernel do it for
    // us; the kernel guarantees calls to write are atomic on the
    // file object, so gather up all we want to print, and make a
    // single system call.

    char out[RECORD_SIZE * 5];
    // lines two and three are at most RECORD_SIZE*2,
    // line one should be much less than RECORD_SIZE
    char *off = out;
    off += sprintf(off, "%s:\n", label);
    for (int i = 0; i < sz; i++) off += sprintf(off, "%02x", decrypted_buf[i]);
    off += sprintf(off, "\n");
    for (int i = 0; i < sz; i++)
      off += sprintf(off, "%c ",
                     isprint(decrypted_buf[i]) ? decrypted_buf[i] : ' ');
    off += sprintf(off, "\n");
    write(transcriptfd, out, off - out);
    if (std::string(label) == "from server") {
      std::cout << "\033[31m" << std::string(out, off - out) << "\033[0m";
    } else if (std::string(label) == "from client") {
      std::cout << "\033[32m" << std::string(out, off - out) << "\033[0m";
    }

    // send it on its way to its destination
    write(writefd, buf, sz);
	
	// Write it to the raw binary format.
    write(rawfd, partial_decrypted_buf, sz);
  }
}

bool has_two_newlines(char *buf, ssize_t sz) {
  int n = 0;
  for (int i = 0; i < sz; i++)
    if (buf[i] == '\n') n++;
  return n >= 2;
}

int main(int argc, char** argv) {
  int clientfd = open_port(12022);
  int serverfd = open_port(12021);
  char buf[130];
  ssize_t pos = 0;

  while (!has_two_newlines(buf, pos)) {
    ssize_t rc = read(clientfd, buf, sizeof(buf) - 1 - pos);
    if (rc == 0) merror("client ended unexpectedly");
    if (rc == -1) perror("client read");
    pos += rc;
  }
  buf[pos] = '\0';
  fputs(buf, stdout);

  read(serverfd, key, 16);
  std::cout << "key: " << std::endl;
  for (int i = 0; i < 16; ++i) {
    std::cout << std::hex << (unsigned int)key[i] << " ";
  }
  std::cout << std::endl;
  send(clientfd, key, 16, MSG_WAITALL);

  int transcriptfd = creat("transcript.txt", S_IRUSR | S_IWUSR | S_IRGRP |
                                                 S_IWGRP | S_IROTH | S_IWGRP);

  int raw_server_fd = creat("server_raw", S_IRUSR | S_IWUSR | S_IRGRP |
                                                 S_IWGRP | S_IROTH | S_IWGRP);

  int raw_client_fd = creat("client_raw", S_IRUSR | S_IWUSR | S_IRGRP |
                                                 S_IWGRP | S_IROTH | S_IWGRP);
  std::string cipher;
  if (argc > 1) {						 
	std::ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "\033[33mWarning: failed to load cipher file." << std::endl;
	} else {
		cipher = std::string((std::istreambuf_iterator<char>(infile)),
					 std::istreambuf_iterator<char>());
	}
  } else {
	  std::cerr << "\033[33mWarning: no cipher file loaded. Second-layer encryption will not be removed.\nUsage: " << argv[0] << " <cipher-file>" << std::endl;
  }

  pid_t from_server_pid;
  pid_t from_client_pid;
  from_server_pid = fork();
  if (from_server_pid == 0) {
    record(serverfd, clientfd, transcriptfd, raw_server_fd, cipher, "from server");
    return 0;
  }
  from_client_pid = fork();
  if (from_client_pid == 0) {
    record(clientfd, serverfd, transcriptfd, raw_client_fd, cipher, "from client");
    return 0;
  }

  // okay, we've been a good mother and made some children.  Let's
  // kick it and just read annotations from standard in and copy them
  // into the transcript (atomically).
  char annotation[80];
  while (fgets(annotation, 80, stdin) != NULL) {
    write(transcriptfd, annotation, strlen(annotation));
  }

  int status;
  if (-1 == waitpid(from_server_pid, &status, 0))
    perror("waiting on server child");
  if (-1 == waitpid(from_client_pid, &status, 0))
    perror("waiting on client child");
  close(clientfd);
  close(serverfd);
  close(transcriptfd);
  return 0;
}
