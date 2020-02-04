# Setup

* Introduction
* Reverse Engineering/Binary Exploitation
	* Disassemblers/Decompiler
	* Debuggers
	* Exploit library
* Cryptography
	* Pencil Paper
	* Math library
	* Scripting
* Web
	* Browser Proxy
	* HTTP library

<h2 id="intro">Introduction</h2>

<b>BOOTCAMP: Please have these tools installed before the bootcamp!</b>

This document list the minimum tool you need installed but also the main ones used in CTFs. The tools are arranged by the four "classic" categories:
* Reverse engineering
* Binary exploitation (aka pwn)
* Cryptography
* Web

<h2 id="rev">Reverse Engineering/Binary Exploitation</h2>

* Disassembler: A tool used to translate machine language into assembly
* Decompiler: A tool that attempts to reconstruct the source code of the compiled program. 
	* [GHIDRA](https://ghidra-sre.org/): A free reverse engineering framework
	* [OpenJDK](https://jdk.java.net/archive/): You might need this for GHIDRA
* Exploit Library: A library with functions used for automating exploit writing
	* [pwntools](http://docs.pwntools.com/): A popular exploit library

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
