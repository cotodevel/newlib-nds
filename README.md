06/04/2018:
Micro$oft has acquired github, you can find updates from this software at: https://coto88.bitbucket.io/
Have a good day.

Update:
3/3/2018
If you already installed Newlib 2.1 for Nintendo DS before, 
please remove c:/toolchain_generic folder completely, then follow the below steps for full install.

These sources are Newlib 2.1 for Nintendo DS, you need to rebuild it so ToolchainGenericDS will use it, then other projects.

You can check a copy of these steps at:
https://github.com/cotodevel/newlib-nds

Requirements: 
-  Internet Connection (for MinGW setup)
-  Windows7 or higher / Linux

For building the toolchain you need three steps:

1) Recompile Newlib 2.1 for Nintendo DS (this guide, keep reading)
2) Recompile ToolchainGenericDS (optional, not on this guide)
3) Recompile project (optional, not on this guide)


Steps:

[Windows]
1.a)You WILL need to install Visual C++ Redistributable Visual Studio 2012 Update 4 installer, get it here:
	https://www.microsoft.com/es-es/download/details.aspx?id=30679
	Download and install the x32 package and install. (This setup distributes bin2c.exe as x86 binaries)
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

1.c)Building Newlib 2.1: 
- Proceed to:
	https://github.com/cotodevel/newlib-nds/blob/master/newlib-nds/README.MD


[Linux]
1.a)Building Newlib 2.1: 
- Proceed to:
	https://github.com/cotodevel/newlib-nds/blob/master/newlib-nds/README.MD
	requires the SAME terminal to be open when compiling: newlib for NDS, ToolchainGenericDS, and Project Specific TGDS


After a while, Newlib 2.1 will be recompiled for ToolchainGenericDS successfully.

What's next: to build ToolchainGenericDS (with Newlib 2.1 sources) visit:
https://github.com/cotodevel/ToolchainGenericDS


Coto