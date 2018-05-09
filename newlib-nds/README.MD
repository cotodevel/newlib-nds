Compile:
[Windows]
 - make clean (everytime you make clean, you must re-do the install step. Which is execute /installer/windows/setup.bat)
 - make

[Linux]
-environment tested: xubuntu/ubuntu x64 14.04 
Open a terminal, execute these 3 commands before compile (enter password if required)
 - su $USER
 - chmod +x env_vars.source
 - . ./env_vars.source
 - make clean
 - make
 
 Linux Notes: 
	-	Keep in mind that if you close the shell/terminal you need to repeat the above [Linux] steps everytime you want to recompile a TGDS project.
	-	Sometimes the packages will fail to download, make sure all packages required by newlib-nds are installed (when you type make), otherwise newlib-nds won't compile.
		(This means the newlib-nds should not return an ERROR rule then exit, but instead should begin compiling a lot of code.)