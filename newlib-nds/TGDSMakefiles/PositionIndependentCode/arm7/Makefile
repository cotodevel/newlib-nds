#
#			Copyright (C) 2017  Coto
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful, but
#WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
#USA
#


# relative path (if you are outside arm9 folder then $(DIR_ARM9), arm7 is $(DIR_ARM7))
RELATIVE_PATH =	

#Prepare ARM7 dirs
DIRLIBS_HDR = $(foreach dirres,$(DIRS_ARM7_HEADER),-I "$(CURDIR)/$(RELATIVE_PATH)/$(dirres)/" )	$(DIRLIBS_ALLOWED)	$(TARGET_LIBRARY_HEADERS_7_INC)
DIRLIBS_SRC = $(foreach dirres,$(DIRS_ARM7_SRC),-I "$(CURDIR)/$(RELATIVE_PATH)/$(dirres)/" )

file_arm7_src_c=  $(foreach dir,$(DIRS_ARM7_SRC), $(subst $(CURDIR)/$(RELATIVE_PATH)/$(dir)/,,$(wildcard $(CURDIR)/$(RELATIVE_PATH)/$(dir)/*.c))  )
file_arm7_src_s=  $(foreach dir,$(DIRS_ARM7_SRC), $(subst $(CURDIR)/$(RELATIVE_PATH)/$(dir)/,,$(wildcard $(CURDIR)/$(RELATIVE_PATH)/$(dir)/*.s))  )
file_arm7_src_SUPP=  $(foreach dir,$(DIRS_ARM7_SRC), $(subst $(CURDIR)/$(RELATIVE_PATH)/$(dir)/,,$(wildcard $(CURDIR)/$(RELATIVE_PATH)/$(dir)/*.S))  )
file_arm7_src_cpp=  $(foreach dir,$(DIRS_ARM7_SRC), $(subst $(CURDIR)/$(RELATIVE_PATH)/$(dir)/,,$(wildcard $(CURDIR)/$(RELATIVE_PATH)/$(dir)/*.cpp))  )
file_arm7_src_bin=  $(foreach dir,$(DIRS_ARM7_SRC), $(subst $(CURDIR)/$(RELATIVE_PATH)/$(dir)/,,$(wildcard $(CURDIR)/$(RELATIVE_PATH)/$(dir)/*.bin))  )

# Object Target
objs_arm7:=	${file_arm7_src_c:.c=.o}	${file_arm7_src_s:.s=.o}	${file_arm7_src_SUPP:.S=.o}		${file_arm7_src_cpp:.cpp=.o}	${file_arm7_src_bin:.bin=.o}
d_objs_arm7:=	${file_arm7_src_c:.c=.d}	${file_arm7_src_s:.s=.d}	${file_arm7_src_SUPP:.S=.d}	${file_arm7_src_cpp:.cpp=.d}

#ARM7 specific definitions. -fno-common so we force initialized data to rodata
MAPFILE = $(DIR_ARM7).map
AS_ASFLAGS		=	$(GLOBAL_SHARED_FLAGS_7)	$(SPECIFIC_AS_COMPILER_FLAGS_7)		$(GLOBAL_AS_COMPILER_FLAGS)
CC_ASFLAGS		=	$(GLOBAL_SHARED_FLAGS_7)	$(SPECIFIC_CXX_COMPILER_FLAGS_7)	$(GLOBAL_CC_COMPILER_FLAGS)
CPP_FLAGS		=	$(GLOBAL_SHARED_FLAGS_7)	$(SPECIFIC_CXX_COMPILER_FLAGS_7)	$(GLOBAL_CXX_COMPILER_FLAGS)
BUILD			= 	$(BUILD_ARM7)
DIR_SRC			= 	$(DIRS_ARM7_SRC)

#--gc-sections: allows relocatable sections linked (already) to be included, otherwise unused sections are discarded.
#check arm9.map "Discarded input sections" to see --gc-sections in action.
LDFLAGS	=	-specs=$(TARGET_LIBRARY_LINKER_PATH_LD)/nds_arm7_ld.specs	-Wl,--no-gc-sections,-Map,$(MAPFILE),--fix-v4bx
LIBRARIES =	-liberty	-l$(TARGET_LIBRARY_NAME_7)	-lsupc++	-lstdc++	-lcnano7	-lgcc

################################################################################################

#Dont modify anything else if not necessary ..
OBJECTS:=	$(objs_arm7)	
OBJDIR 	=	./$(BUILD)
VPATH 	=	$(DIR_SRC)
OBJPROG =	$(addprefix $(OBJDIR)/, $(ELF_ARM7))


all: $(OBJDIR)	$(OBJPROG)
#all: debug

#Check $(OBJDIR) if not exists: create it
$(OBJDIR):
	-@echo "Folder $(OBJDIR) does not exist. Creating"
	-mkdir -p $(CURDIR)/../../$(DIR_ARM7)/$(BUILD)
	-mkdir -p $@

#rule for reading *.bin in /data folder, converts to .C source code, which then gets compiled as object so it can be linked later
$(OBJDIR)/%.o : %.bin
	-@echo 'trying to convert .BIN ($<) -> .C output: ${@:.o=.c} : arrayName: $(subst build/,,${@:.o=})'
	$(BIN2C)	$<	${@:.o=.c}	$(subst build/,,${@:.o=})
	$(CC)	$(CC_ASFLAGS)	-fPIC	$(DIRLIBS_HDR)	$(DIRLIBS_SRC)	$(DIRLIBS_PROHIBITED)	-o $@ -c ${@:.o=.c}

#Do C Compile now!
$(OBJDIR)/%.o : %.c
	-@echo 'C Compile start: $@'
	$(CC)	$(CC_ASFLAGS)	-fPIC	$(DIRLIBS_HDR)	$(DIRLIBS_SRC)	$(DIRLIBS_PROHIBITED)	-o $@ -c $<
	-@echo 'C Compile End: $@'

#Do C++ (CXX) Compile now!
$(OBJDIR)/%.o : %.cpp
	-@echo 'C++ Compile start: $@'
	$(CPP)	$(CPP_FLAGS)	-fPIC	$(DIRLIBS_HDR)	$(DIRLIBS_SRC)	-o $@ -c $<
	-@echo 'C Compile End: $@'

#Coto: Special "exception" rule. Fixes tricky projects such as SnemulDS's opcodes2.s where GCC AS is used, while compatibility with .S is required for newer projects.
#.S is GCC CC/CPP for compiling assembler with cpp headers
#.s is GCC AS Assembler for compiling assembler the usual way

#Do s (GCC AS) Compile now!
$(OBJDIR)/%.o : %.s
	-@echo 's Compile start: $@'
	$(AS)	$(DIRLIBS_HDR)	$(DIRLIBS_SRC)	$(AS_ASFLAGS)	-o $@ -c $<
	-@echo 's Compile end: $@'

#Do S (GCC CC) Compile now!
$(OBJDIR)/%.o : %.S
	-@echo 'S Compile start: $@'
	$(CPP)	-x assembler-with-cpp	$(DIRLIBS_HDR)	$(DIRLIBS_SRC)	$(CC_ASFLAGS)	-o $@ -c $<
	-@echo 'S Compile end: $@'
	
################################################################################################
$(OBJPROG): $(addprefix $(OBJDIR)/, $(OBJECTS))
	-@echo 'PIC object generated: $<'

clean:
	-@echo 'cleanup -fPIC $(DIR_ARM7)'
	-@rm -fr $(BUILD)	$(CURDIR)/../../$(DIR_ARM7)/$(BUILD)