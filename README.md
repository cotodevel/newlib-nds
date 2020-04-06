[Newlib for NintendoDS]
These sources are Newlib + ARM specific drivers, for Nintendo DS and it's the baremetal OS ToolchainGenericDS requires, thus, ToolchainGenericDS projects as well.
You need to rebuild it at least once. And then ToolchainGenericDS and then ToolchainGenericDS project(s).

It relies on ARM EABI components, (and not ARM NONE EABI components, thus any object using that format will not be compatible). 
This decision was made becase it builds smaller binaries and they are 30% faster.

You can check a copy of these steps at:
https://bitbucket.org/Coto88/newlib-nds

Version: 
	Windows : GCC 4.9.2 (ARM EABI)
	Linux : GCC 6.x.x+	(ARM NONE EABI)

Features:
- GAS (Gnu Assembler): .s / .S ARM assembler files, using the GNU syntax.
- C support (malloc, full POSIX file implementation): .c files, using the GNU syntax.
- C++ STL support (new / delete operators implemented): .cpp/.hpp files, using the GNU syntax.

Note on C++ projects:
- 	It has overhead. A barebones C TGDS project is roughly 200K, where as C++ using <vector> <iostream> might use about 580K. 
- 	While classes and templates are working, new/delete operators rely on malloc/free newlib implementation by design, 
	this means there is NO garbage collector, and you MUST keep track of allocated/freed classes or you are guaranteed to get undefined behaviour.

Requirements: 
-  Internet Connection (for MinGW setup)
-  Windows7 or higher / Linux

For building the toolchain you need three steps:

1) Recompile Newlib for Nintendo DS (this guide, keep reading)
2) Recompile ToolchainGenericDS (optional, not on this guide)
3) Recompile project (optional, not on this guide)


Steps:

[Windows]
1.a)You WILL need to install Visual C++ Redistributable Visual Studio 2012 Update 4 installer, get it here:
	https://www.microsoft.com/es-es/download/details.aspx?id=30679
	Download and install the x86 package and install. (This setup distributes bin2c.exe as x86 binaries)
	(if you skip this step, most C++ code that helps TGDS will fail, so don't skip it...)
	Note: if you wish to use the x64 version, you must recompile the source as x64 binary and install the above package as x64 installer.

-	Head to /installer/windows/

-	Run setup.bat
	
1.b)Once copy is done, a MingGW setup will appear.
	
-	The installation Path recommended by default: C:\MinGW
-	While running setup, wait until Continue button appears. Then you must choose: 
		mingw-developer-toolkit then Mark For Installation. Click: Installation> Apply Changes then Apply. Setup will begin. 
-	Wait for the Close button to appear, close setup. Head to C:/MinGW/msys/1.0/
-	Copy a msys.bat shortcut from the same file here, to your desired place, this is the minimal console required to build ToolchainGenericDS projects. 
	By default, you can Unzip/make (build) projects from within: C:/MinGW/msys/1.0/home folder.

1.c)Building Newlib for NintendoDS: 
- Proceed to:
	https://bitbucket.org/Coto88/newlib-nds/src/master/newlib-nds/README.MD

[Linux]
1.a)Building Newlib for NintendoDS: 

- Requires Ubuntu 14.04 or later (kubuntu, xubuntu or others working as well). Proceed to:
	https://bitbucket.org/Coto88/newlib-nds/src/master/newlib-nds/README.MD
	requires the SAME terminal to be open when compiling: newlib for NDS, ToolchainGenericDS, and Project Specific TGDS

After a while, Newlib for NintendoDS will be recompiled for ToolchainGenericDS successfully.


Next: 
build ToolchainGenericDS:
https://bitbucket.org/Coto88/toolchaingenericds

Coto