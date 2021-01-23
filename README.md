[Newlib for NintendoDS]
These sources are Newlib + ARM specific drivers, for Nintendo DS and it's the baremetal OS ToolchainGenericDS requires, thus, ToolchainGenericDS projects as well.
You need to rebuild it at least once. And then ToolchainGenericDS and then ToolchainGenericDS project(s).

You can check a copy of these steps at:
https://bitbucket.org/Coto88/newlib-nds

Version: 
	Windows : Clang 8.0.1
	Linux : GCC 4.9.3	(ARM NONE EABI)

Features:
- GAS (Gnu Assembler): .s / .S ARM assembler files, using the GNU syntax.
- Clang 8.0.1 / GCC: C support (malloc, full POSIX file implementation): .c files, using the GNU syntax.
- Clang 8.0.1 / GCC: C++ STL support (new / delete operators implemented): .cpp/.hpp files, using the GNU syntax.

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
	
1.b)Right after, a CYGWIN setup wizard will appear. Click next until a list of mirrors appear, choose the first one or subsequently the others if the first didn't work.

- Then type "make" in the package, choose the vanilla make (4.3-1). The "Skip" checkbox will change and instead the version will appear.

- Cleanup and write "clang" and repeat the same steps. Choose mingw64-x86_64-clang (8.0.1-1).

- Cleanup and write "llvm" and repeat the same steps. Choose mingw64-x86_64-llvm (5.0.1-1) and llvm (5.0.1-1).


Click next until the setup ends.

Finally, place ";C:\cygwin64\bin" at the end of the "Path" SYSTEM variable, semicolon included, so that the Cygwin toolset is available for use.
Right-click Start (lower-left on Start menu)
Click Search
Type env into search box
Click Edit the system environment variables/Control Panel

From now on, use CYGWIN terminal to build TGDS projects.

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