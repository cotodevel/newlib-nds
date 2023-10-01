Compile:

[Windows]
 - make clean (everytime you do this, you must run again newlib-nds/installer/windows/setup.bat)
 - make


[Linux]
 - make clean
 - make
 
 Linux Notes: 
	-	Sometimes the packages will fail to download, make sure all packages required by newlib-nds are installed (when you type make), otherwise newlib-nds won't compile.
		(This means the newlib-nds should not return an ERROR rule then exit, but instead should begin compiling a lot of code.)