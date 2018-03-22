Compile:
[Windows]
 - make clean 
 - make

[Linux]
-environment tested: xubuntu/ubuntu x64 14.04 
Open a terminal, execute these 3 commands before compile (enter password if required)
 - su $USER
 - chmod +x env_vars.source
 - . ./env_vars.source
 - make clean
 - make
 
 Linux: Keep in mind that if you close the shell/terminal you need to repeat the above [Linux] steps everytime you want to recompile a TGDS project.