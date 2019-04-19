These are the default Makefiles a TGDS project is built with (for both ARM7 and ARM9 cores)
if the below condition in TGDSProject/Makefile is set to "default" (   See 1)   ), then 
default Makefile is used to compile TGDS project.

1)
$(SOURCE_MAKEFILE7) = "default"
$(SOURCE_MAKEFILE9) = "default"

2)
Otherwise, if the below condition, in TGDSProject/Makefile is set to "custom", the Makefiles are custom tailored per project. 
$(SOURCE_MAKEFILE7) = "custom"
$(SOURCE_MAKEFILE9) = "custom"

Clean rules should cleanup these Makefiles if condition 1) is true.

- 

also PositionIndependentCode folder has a copy of the above Makefiles, but the generated code is -fPIC (Position Independent Code), and since the linker is capable of
mixing PIC and non-PIC code directly, we give that feature to TGDS directly ;-) . 

What does this mean:
A TGDS 1.5 project has a PositionIndependentCode folder, where each arm7/arm9 folder PositionIndependentCode is capable of compiling PIC code and linking it directly into
the TGDS binary. Otherwise leave these blank