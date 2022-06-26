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

#TGDS1.6 compatible Makefile

#ToolchainGenericDS specific: Use Makefiles from either TGDS, or custom
export SOURCE_MAKEFILE7 = custom
export SOURCE_MAKEFILE9 = custom

#Shared
ifeq ($(TGDS_ENV),windows)	
	include $(DEFAULT_GCC_PATH)/Makefile.basenewlib
endif
ifeq ($(TGDS_ENV),linux)
	include $(CURDIR)/../installer/shared/6.2_2016q4/Makefile.basenewlib
endif


#Custom
export TARGET_LIBRARY_NAME_7 = cnano7
export TARGET_LIBRARY_NAME_9 = cnano9

export BINSTRIP_RULE_7 =	arm7.bin
export BINSTRIP_RULE_9 =	arm9.bin
export DIR_ARM7 = arm7
export BUILD_ARM7	=	build
export DIR_ARM9 = arm9
export BUILD_ARM9	=	build
export ELF_ARM7 = arm7.elf
export ELF_ARM9 = arm9.elf

export TARGET_LIBRARY_FILE_7	:=	lib$(TARGET_LIBRARY_NAME_7).a
export TARGET_LIBRARY_FILE_9	:=	lib$(TARGET_LIBRARY_NAME_9).a

#NDS Newlib nano flags
export NEWLIB_NANO_COMPILE_FLAGS_C	:=		\
										-D_SC_PAGE_SIZE	-DSEPARATE_OBJECTS	-D_DOUBLE_IS_32BITS	-D_SOFTFP__	-DDEFINE_MEMALIGN	\
										-DL_arm_negdf2	-DL_arm_addsubdf3	-DL_arm_muldivdf3	-DL_arm_cmpdf2	-DL_arm_unorddf2	-DL_arm_fixdfsi	-DL_arm_fixunsdfsi	-DL_arm_truncdfsf2	\
										-DHAVE_INITFINI_ARRAY	-D'malloc_getpagesize=128'	-D'HAVE_MMAP=0'	\
										-DL_arm_negsf2	-DL_arm_addsubsf3	-DL_arm_muldivsf3	-DL_arm_cmpsf2	-DL_arm_unordsf2	-DL_arm_fixsfsi	-DL_arm_fixunssfsi	\
										-DL_aeabi_lcmp	-DL_aeabi_ulcmp	-DL_aeabi_ldivmod	-DL_aeabi_uldivmod	-DL_fixdfdi	-D_LDBL_EQ_DBL	-D'__ISO_C_VISIBLE=1999'	-D_GNU_SOURCE	-D_GLIBCXX_USE_WCHAR_T	-D_ISOC99_SOURCE	-D_GLIBCXX_HOSTED	-D_GLIBCXX_USE_CXX11_ABI=0	-D_GLIBCXX17_DEPRECATED=0	-DSOFTFLOAT_FOR_GCC
export NEWLIB_NANO_COMPILE_FLAGS_C_9	:=	-DDEFINE_MALLOC	-DDEFINE_FREE	-DDEFINE_CALLOC	-DDEFINE_REALLOC	-DDEFINE_MALLOC_USABLE_SIZE	-DDEFINE_CFREE	-D_GLIBCXX_ASSERTIONS	$(NEWLIB_NANO_COMPILE_FLAGS_C)


#should reflect all the above defs
export NEWLIB_NANO_COMPILE_FLAGS_ASM	:=	-defsym _DOUBLE_IS_32BITS='1'	-defsym _SOFTFP__='1'
export NEWLIB_NANO_COMPILE_FLAGS_ASM9	:=	$(NEWLIB_NANO_COMPILE_FLAGS_ASM)	-defsym DEFINE_MALLOC='1'	-defsym DEFINE_FREE='1'	-defsym DEFINE_CALLOC='1'	-defsym DEFINE_REALLOC='1'	-defsym DEFINE_MALLOC_USABLE_SIZE='1'

export LIBSTDCPPFLAGS	=			-D__cpp_aligned_new		-D'__cplusplus=201103L'

.SUFFIXES: .all
#####################################################ARM7#####################################################
#the correct format is : ../include/sys/ otherwise recursive folders break in later bash scripts
export DIRS_ARM7_SRC = ../../newlib-src/libgloss/	\
			../../newlib-src/config/arm/	\
			../../newlib-src/newlib/libc/include/	\
			../../newlib-src/libgloss/arm/	\
			../../newlib-src/libgloss/arm/gcc/	\
			../../newlib-src/newlib/libc/argz/	\
			../../newlib-src/newlib/libc/ctype/	\
			../../newlib-src/newlib/libc/errno/	\
			../../newlib-src/newlib/libc/locale/	\
			../../newlib-src/newlib/libc/machine/arm/	\
			../../newlib-src/newlib/libc/misc/	\
			../../newlib-src/newlib/libc/posix/	\
			../../newlib-src/newlib/libc/reent/	\
			../../newlib-src/newlib/libc/search/	\
			../../newlib-src/newlib/libc/signal/	\
			../../newlib-src/newlib/libc/stdio/	\
			../../newlib-src/newlib/libc/stdlib/	\
			../../newlib-src/newlib/libc/string/	\
			../../newlib-src/newlib/libc/sys/arm/	\
			../../newlib-src/newlib/libc/sys/arm/sys/	\
			../../newlib-src/newlib/libc/sys/arm/linux/	\
			../../newlib-src/newlib/libc/syscalls/	\
			../../newlib-src/newlib/libc/time/	\
			../../newlib-src/newlib/libc/unix/	\
			../../newlib-src/newlib/libc/xdr/	\
			../../newlib-src/newlib/	\
			../../newlib-src/newlib/libm/common/	\
			../../newlib-src/newlib/libm/complex/	\
			../../newlib-src/newlib/libm/machine/arm/	\
			../../newlib-src/newlib/libm/math/	\
			../../newlib-src/newlib/libm/mathfp/
			
export DIRS_ARM7_HEADER = ../../newlib-src/libgloss/	\
			../../newlib-src/config/arm/	\
			../../newlib-src/libgloss/arm/	\
			../../newlib-src/libgloss/arm/gcc/	\
			../../newlib-src/newlib/libc/argz/	\
			../../newlib-src/newlib/libc/ctype/	\
			../../newlib-src/newlib/libc/errno/	\
			../../newlib-src/newlib/libc/locale/	\
			../../newlib-src/newlib/libc/machine/arm/	\
			../../newlib-src/newlib/libc/machine/arm/machine/	\
			../../newlib-src/newlib/libc/include/	\
			../../newlib-src/newlib/libc/include/rpc/	\
			../../newlib-src/newlib/libc/include/sys/	\
			../../newlib-src/newlib/libc/include/machine/	\
			../../newlib-nds/newlib-nds-headers/	\
			../../newlib-nds/newlib-nds-headers/sys/	\
			../../newlib-src/newlib/libc/misc/	\
			../../newlib-src/newlib/libc/posix/	\
			../../newlib-src/newlib/libc/reent/	\
			../../newlib-src/newlib/libc/search/	\
			../../newlib-src/newlib/libc/signal/	\
			../../newlib-src/newlib/libc/stdio/	\
			../../newlib-src/newlib/libc/stdlib/	\
			../../newlib-src/newlib/libc/string/	\
			../../newlib-src/newlib/libc/sys/arm/	\
			../../newlib-src/newlib/libc/sys/arm/sys/	\
			../../newlib-src/newlib/libc/sys/linux/	\
			../../newlib-src/newlib/libc/syscalls/	\
			../../newlib-src/newlib/libc/time/	\
			../../newlib-src/newlib/libc/unix/	\
			../../newlib-src/newlib/libc/xdr/	\
			../../newlib-src/newlib/	\
			../../newlib-src/newlib/libm/common/	\
			../../newlib-src/newlib/libm/complex/	\
			../../newlib-src/newlib/libm/machine/arm/	\
			../../newlib-src/newlib/libm/math/	\
			../../newlib-src/newlib/libm/mathfp/
			
#####################################################ARM9#####################################################

export DIRS_ARM9_SRC = ../../newlib-src/libgloss/	\
			../../newlib-src/config/arm/	\
			../../newlib-src/newlib/libc/include/	\
			../../newlib-src/libgloss/arm/	\
			../../newlib-src/libgloss/arm/gcc/	\
			../../newlib-src/newlib/libc/argz/	\
			../../newlib-src/newlib/libc/ctype/	\
			../../newlib-src/newlib/libc/errno/	\
			../../newlib-src/newlib/libc/locale/	\
			../../newlib-src/newlib/libc/machine/arm/	\
			../../newlib-src/newlib/libc/misc/	\
			../../newlib-src/newlib/libc/posix/	\
			../../newlib-src/newlib/libc/reent/	\
			../../newlib-src/newlib/libc/search/	\
			../../newlib-src/newlib/libc/signal/	\
			../../newlib-src/newlib/libc/stdio/	\
			../../newlib-src/newlib/libc/stdlib/	\
			../../newlib-src/newlib/libc/string/	\
			../../newlib-src/newlib/libc/sys/arm/	\
			../../newlib-src/newlib/libc/sys/arm/sys/	\
			../../newlib-src/newlib/libc/sys/arm/linux/	\
			../../newlib-src/newlib/libc/syscalls/	\
			../../newlib-src/newlib/libc/time/	\
			../../newlib-src/newlib/libc/unix/	\
			../../newlib-src/newlib/libc/xdr/	\
			../../newlib-src/newlib/	\
			../../newlib-src/newlib/libm/common/	\
			../../newlib-src/newlib/libm/complex/	\
			../../newlib-src/newlib/libm/machine/arm/	\
			../../newlib-src/newlib/libm/math/	\
			../../newlib-src/newlib/libm/mathfp/
			
export DIRS_ARM9_HEADER = ../../newlib-src/libgloss/	\
			../../newlib-src/config/arm/	\
			../../newlib-src/libgloss/arm/	\
			../../newlib-src/libgloss/arm/gcc/	\
			../../newlib-src/newlib/libc/argz/	\
			../../newlib-src/newlib/libc/ctype/	\
			../../newlib-src/newlib/libc/errno/	\
			../../newlib-src/newlib/libc/locale/	\
			../../newlib-src/newlib/libc/machine/arm/	\
			../../newlib-src/newlib/libc/machine/arm/machine/	\
			../../newlib-src/newlib/libc/include/	\
			../../newlib-src/newlib/libc/include/rpc/	\
			../../newlib-src/newlib/libc/include/sys/	\
			../../newlib-src/newlib/libc/include/machine/	\
			../../newlib-nds/newlib-nds-headers/	\
			../../newlib-nds/newlib-nds-headers/sys/	\
			../../newlib-src/newlib/libc/misc/	\
			../../newlib-src/newlib/libc/posix/	\
			../../newlib-src/newlib/libc/reent/	\
			../../newlib-src/newlib/libc/search/	\
			../../newlib-src/newlib/libc/signal/	\
			../../newlib-src/newlib/libc/stdio/	\
			../../newlib-src/newlib/libc/stdlib/	\
			../../newlib-src/newlib/libc/string/	\
			../../newlib-src/newlib/libc/sys/arm/	\
			../../newlib-src/newlib/libc/sys/arm/sys/	\
			../../newlib-src/newlib/libc/sys/linux/	\
			../../newlib-src/newlib/libc/syscalls/	\
			../../newlib-src/newlib/libc/time/	\
			../../newlib-src/newlib/libc/unix/	\
			../../newlib-src/newlib/libc/xdr/	\
			../../newlib-src/newlib/	\
			../../newlib-src/newlib/libm/common/	\
			../../newlib-src/newlib/libm/complex/	\
			../../newlib-src/newlib/libm/machine/arm/	\
			../../newlib-src/newlib/libm/math/	\
			../../newlib-src/newlib/libm/mathfp/

	# Build Target(s)	(both processors here)
all: compilelib
#all: debug
#Make. Also copy libc headers and own nds-headers. Must resemble the windows folder structure 
compilelib	:
	$(MAKE)	setup
	$(MAKE)	copylibs
ifeq ($(TGDS_ENV),linux)
	sudo chmod -R 777	$(DEFAULT_GCC_PATH)../../
endif
	$(MAKE)	-R	-C	$(DIR_ARM7)/
	$(MAKE)	-R	-C	$(DIR_ARM9)/

#---------------------------------------------------------------------------------
# Clean
clean:
	$(MAKE)	clean	-C	$(DIR_ARM7)/
ifeq ($(SOURCE_MAKEFILE7),default)
	-@rm -rf $(CURDIR)/$(DIR_ARM7)/Makefile
endif
	$(MAKE)	clean	-C	$(DIR_ARM9)/
ifeq ($(SOURCE_MAKEFILE9),default)
	-@rm -rf $(CURDIR)/$(DIR_ARM9)/Makefile
endif
ifeq ($(TGDS_ENV),windows)
	-@rm -rf $(TARGET_LIBRARY_HEADERS_7)	$(TARGET_LIBRARY_HEADERS_9)	$(TARGET_LIBRARY_PATH)$(TARGET_LIBRARY_LINKER_SRC)
	-@rm -rf	$(DEFAULT_GCC_PATH)../
endif
ifeq ($(TGDS_ENV),linux)
	-@sudo rm -rf	$(DEFAULT_GCC_PATH)	$(CURDIR)/temp	$(CURDIR)/../installer/linux/Coto88-packages-259926b7da68
	-@sudo rm	/usr/bin/bin2c	$(CURDIR)/../installer/linux/toolchain.zip
	$(MAKE)	cleanstuff
endif

setup:
ifeq ($(TGDS_ENV),windows)	
	-@echo 'windows:ignore rule.'
endif
ifeq ($(TGDS_ENV),linux)
	- sudo apt-get update
	- sudo apt-get -f install -y gcc-mingw-w64-i686 g++-mingw-w64-i686 binutils-mingw-w64-i686 \
		build-essential automake libtool lib32z1 lib32ncurses-dev libmpc-dev libgmp3-dev	\
		libmpfr-dev zlib1g-dev autoconf autogen bison dejagnu flex gcc-9-i686-linux-gnu gcc-i686-linux-gnu \
		flip gawk git gperf gzip nsis openssh-client p7zip-full perl python-dev-is-python2 libisl-dev \
		scons tcl texinfo tofrodos wget zip texlive texlive-extra-utils	g++ 
endif

#rule already validated == linux
buildtgdsdutils:
	-@wget	-O $(CURDIR)/temp/toolchaingenericds-utils.zip	https://bitbucket.org/Coto88/toolchaingenericds-utils/get/master.zip
	-@7z x $(CURDIR)/temp/toolchaingenericds-utils.zip	-o$(CURDIR)/temp
	-@sudo $(MAKE)	-C	$(CURDIR)/temp/Coto88-toolchaingenericds-utils-ec52108eacf1/
	-@sudo mv	$(CURDIR)/temp/Coto88-toolchaingenericds-utils-ec52108eacf1/toolchaingenericds-utils	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)toolchaingenericds-utils

buildgrit:
	-@sudo	$(MAKE) -C 	$(CURDIR)/../installer/linux/Coto88-packages-259926b7da68/tgds-packages/grit_linux_18_04/FreeImage all
	-@sudo	$(MAKE) -C 	$(CURDIR)/../installer/linux/Coto88-packages-259926b7da68/tgds-packages/grit_linux_18_04/grit_src all
	-@sudo mv	$(CURDIR)/../installer/linux/Coto88-packages-259926b7da68/tgds-packages/grit_linux_18_04/grit_src/grit	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)grit

buildndstool:
	-@7z x $(CURDIR)/misc/ndstool-lat.zip	-o$(CURDIR)/misc
	-@sudo $(MAKE)	-C	$(CURDIR)/misc/Coto88-ndstool-fa6b6d018813
	-@sudo $(MAKE)	-C	$(CURDIR)/misc/Coto88-ndstool-fa6b6d018813
	-@sudo mv	$(CURDIR)/misc/Coto88-ndstool-fa6b6d018813/ndstool	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ndstool
	-@sudo rm -rf	$(CURDIR)/misc/Coto88-ndstool-fa6b6d018813

buildffmpeg:
	-@tar -xf $(CURDIR)/../installer/linux/Coto88-packages-259926b7da68/newlib-nds-packages/ffmpeg-4.2.2-i686-static.tar.xz -C $(GCC_BUILD_ENV)$(GCC_BIN_PATH)
	-@sudo mv	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ffmpeg-4.2.2-i686-static/ffmpeg	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ffmpeg
	-@sudo mv	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ffmpeg-4.2.2-i686-static/ffprobe	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ffprobe
	-@sudo mv	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)ffmpeg-4.2.2-i686-static/qt-faststart	$(GCC_BUILD_ENV)$(GCC_BIN_PATH)qt-faststart


buildstuff:
	-rm -fr $(CURDIR)/temp
	-mkdir -p $(CURDIR)/temp
	-$(MAKE)	-f	$(CURDIR)/../installer/linux/Makefile-tgds
	-$(MAKE)	buildtgdsdutils	
	-$(MAKE)	buildgrit
	-$(MAKE)	buildndstool
	-$(MAKE)	buildffmpeg
	
	
#order is important here. 
cleanstuff:
	-$(MAKE)	-C	$(CURDIR)/temp/Coto88-toolchaingenericds-utils-ec52108eacf1/	clean
	-$(MAKE)	-C	$(CURDIR)/../installer/linux/Coto88-packages-259926b7da68/tgds-packages/grit_linux_18_04	clean
	-$(MAKE)	-f	$(CURDIR)/../installer/linux/Makefile-tgds	clean
	
#files renamed to -excluded is because the current toolchain paths are being included (for default GNU ARM tools), EVEN
#when we force -nostdinc++ and -nostdinc. So the files inside TGDS are used
copylibs:
ifeq ($(TGDS_ENV),windows)	
	-mkdir -p $(TARGET_LIBRARY_PATH)
	-cp	-r $(CURDIR)/../newlib-src/newlib/libc/include/	$(TARGET_LIBRARY_PATH)
	-cp	-r $(CURDIR)/../newlib-nds/newlib-nds-headers/	$(TARGET_LIBRARY_PATH)
	-mkdir -p $(TARGET_LIBRARY_LINKER_DEST) && cp	-r $(CURDIR)$(TARGET_LIBRARY_LINKER_SRC) $(TARGET_LIBRARY_LINKER_DEST)
	-cp	-r $(CURDIR)$(TARGET_LIBRARY_MAKEFILES_SRC) $(TARGET_LIBRARY_MAKEFILES_DEST)
endif
ifeq ($(TGDS_ENV),linux)
	-sudo chmod -R 777	$(DEFAULT_GCC_PATH)../../
	-sudo mkdir -p $(DEFAULT_GCC_PATH)
	-sudo cp	-r $(CURDIR)/../installer/shared/6.2_2016q4/	$(DEFAULT_GCC_PATH)/../
	-sudo cp	-r $(CURDIR)/../installer/shared/Makefile.basenewlib	$(DEFAULT_GCC_PATH)/
	-sudo mkdir -p $(TARGET_LIBRARY_PATH)
	-sudo cp	-r $(CURDIR)/../newlib-src/newlib/libc/include/	$(TARGET_LIBRARY_PATH)
	-sudo cp	-r $(CURDIR)/../newlib-nds/newlib-nds-headers/	$(TARGET_LIBRARY_PATH)
	-sudo mkdir -p $(TARGET_LIBRARY_LINKER_DEST) && sudo cp	-r $(CURDIR)$(TARGET_LIBRARY_LINKER_SRC) $(TARGET_LIBRARY_LINKER_DEST)
	-sudo cp	-r $(CURDIR)$(TARGET_LIBRARY_MAKEFILES_SRC) $(TARGET_LIBRARY_MAKEFILES_DEST)
	$(MAKE)	buildstuff
endif

commitChanges:
	-@git commit -a	-m '$(COMMITMSG)'
	-@git push origin HEAD
	

