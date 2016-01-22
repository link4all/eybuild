About eybuild

What is eybuild?
eybuild is WEB development toolkit, in which you can insert C/C++ script
into html/xml files directly. for more see http://www.eybuild.com

FastCGI:
	Please see fastcgi/Readme.txt
	eybuild.0.8.4 and later verion support FastCGI.
	2006-04-25 newzy

more:    
    eybuild@hotmail.com, http://www.eybuild.com
    
install:
    install 1.xx.xx or later version to Linux environment.
	see INSTALL

    install 00.07.00 or later version to Linux environment.
    1. uncompress the install packet
    2. set the environment EYBUILD_BASE pointer to you eybuild work directory
    3. insure all files executable in $(EYBUILD_BASE)/bin
    
demo: 
    running demo in windows, see the manual.
    running demo in linux:
    1. goto the directory $(EYBUILD_BASE)/demo/unix
    2. running the script domap.unix as: ./domap.unix
    3. running Makefile: 'make' or 'make all'
    4. a new file 'demo.cgi' will be created
    5. copy 'demo.cgi' to the webserver cgi-bin directory
    6. access it from browser as: 
       http://127.0.0.1/cgi-bin/demo.cgi

cspengine:
    support from 0.9.8

also see:
    Log.txt License.txt INSTALL http://www.eybuild.com

