[Newlib for NintendoDS]
These sources are Newlib + ARM specific drivers, for Nintendo DS.

Version: 
	Windows/Linux : GCC 4.9.1	(ARM EABI)

Features:
- GAS (Gnu Assembler): .s / .S ARM assembler files, using the GNU syntax.
- GCC: C support (malloc, full POSIX file implementation): .c files, using the GNU syntax.
- GCC: C++ STL support (new / delete operators implemented): .cpp/.hpp files, using the GNU syntax.

1) Recompile Newlib for Nintendo DS (this guide, keep reading)
2) Recompile ToolchainGenericDS (optional, not on this guide)
3) Recompile project (optional, not on this guide)

Steps:

[Windows]
Follow the steps at https://bitbucket.org/Coto88/toolchaingenericds-ide then proceed to [Done].

[Linux]
- 1.a)Building Newlib for NintendoDS: 
	- make clean
	- make
 
Notes: 
	- 	Sometimes the packages will fail to download. Make sure all packages required are installed (when you type make), otherwise newlib-nds won't compile.
		Expected output is a lot of code compiled, then shell is idle.

[Done] If you followed all steps up to this point, newlib for NintendoDS was built correctly. ToolchainGenericDS needs to be built now:
https://bitbucket.org/Coto88/toolchaingenericds

Coto