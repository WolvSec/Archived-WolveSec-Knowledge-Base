# Setup

* [Introduction](#intro)
* [Operating Systems](#os)
* [Reverse Engineering/Binary Exploitation](#rev)
	* Disassemblers/Decompiler
	* Debuggers
	* Exploit library
* [Cryptography](#crypto)
	* Pencil Paper
	* Math library
	* Scripting
* [Web](#web)
	* Browser Proxy
	* HTTP library
* [Misc](#misc)
	* Collaboration

<h2 id="intro">Introduction</h2>

<b>BOOTCAMP: Please have these tools installed before the bootcamp!</b>

This document list the minimum tool you need installed but also the main ones used in CTFs. The tools are arranged by the four "classic" categories:
* Reverse engineering
* Binary exploitation (aka pwn)
* Cryptography
* Web

<h2 id="os">Operating System (OS)</h2>

There is no specific OS required. However, some CTF challenges are written for other platforms so you will want to have access to multiple different OSs.
* Virtualization software: A program that allows you to host multiple operating system. 
	* [VirtualBox](www.virtualbox.org): A virtualization software.
	* [Vmware workstation](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html): A virtualization software. Does not seem to be as easy to install on Mac.
* Operating System: A system software that runs other software
	* [Kali linux](https://www.offensive-security.com/kali-linux-vm-vmware-virtualbox-image-download/): A linux operating system that has already has many security tools installed.
	
	

<h2 id="rev">Reverse Engineering/Binary Exploitation</h2>

* Disassembler: A tool used to translate machine language into assembly
* Decompiler: A tool that attempts to reconstruct the source code of the compiled program. 
	* [GHIDRA](https://ghidra-sre.org/): A free reverse engineering framework
	* [OpenJDK](https://jdk.java.net/archive/): You might need this for GHIDRA
* Debuggers: A tool used to step through a program while it is running
	* [gdb/gef](https://gef.readthedocs.io/): A debugger for UNIX based systems. GEF is a nice plugin for vulnerability discovery
* Exploit Library: A library with functions used for automating exploit writing
	* [pwntools](http://docs.pwntools.com/): A popular exploit library
* Virtualization Software 
	* [CTF VM](https://github.com/gsingh93/ctf-vm): Kindly provided by Umich alumnus gsingh. <b>You'll want this for pwn!</b>

<h2 id="crypto">Cryptography</h2>

* Pencil & Paper: An implement for writing or drawing
	* [BIC pencils](https://www.shopbic.com/products/stationery/pencils/#1): French pencils
* Math Library: A library of functions with mathematical capabilities
	* [Sage Math](https://www.sagemath.org/): Open source math library
* Scripting language: A programming language used for automating tasks
	* [Python](https://www.python.org/): A popular multi-purpose language

<h2 id="web">Web</h2>

* Browser Proxy: A tool to inspect HTTP requests and responses exchanged between your web client and back end.
	* [Burpsuite](https://portswigger.net/burp): A popular browser proxy
* HTTP library: A library for programmatically performing HTTP transactions
	* [HTTP Requests](https://requests.readthedocs.io/): An HTTP library in python

<h2 id="misc">Miscellaneous</h2>

* Collaboration: Tools for improving teamwork
	* [BlueJeans](https://umich.bluejeans.com/): Provided by UMich
