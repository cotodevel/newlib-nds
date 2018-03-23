#let's not override default linux environment variables so we use them to build ndstool
BUILD		:=	build
TARGET		:=	ndstool
BUILD		:=	build
SOURCES		:=	source
INCLUDES	:=	include
DATA		:=	data

#---------------------------------------------------------------------------------
.PHONY: compileNDSTool clean
all: clean	compileNDSTool	$(TARGET)
#all:	debug

#---------------------------------------------------------------------------------
compileNDSTool:
	@make -C $(CURDIR)/DefaultArm7
	@make -C $(CURDIR)/Loader

#---------------------------------------------------------------------------------
#these must come from somewhere... let's skip them since this ndstool fork is used only for building valid NDS binaries
.PHONY: PassMeIncludes
PassMeIncludes: $(BUILD)/passme_vhd1.h $(BUILD)/passme_vhd2.h

$(BUILD)/passme_vhd1.h: $(SOURCES)/passme.vhd
	cat $< | gawk '/^--!/ { COND=1; $$0=""; } // { gsub("\"", "\\\""); gsub("\011", "\\t"); gsub("\015", ""); if (!COND) print "\"" $$0 "\\n\"" }' > $@

$(BUILD)/passme_vhd2.h: $(SOURCES)/passme.vhd
	cat $< | gawk '/^--!/ { COND=1; $$0=""; } // { gsub("\"", "\\\""); gsub("\011", "\\t"); gsub("\015", ""); if (COND) print "\"" $$0 "\\n\"" }' > $@

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@make -C DefaultArm7 clean
	@make -C Loader clean
	@rm -fr $(BUILD) $(OUTPUT)	$(ndstool)	$(LINKABLE_OBJ)	$(LINKABLE_OBJD)
	@sudo rm	-fr	/usr/bin/ndstool

#---------------------------------------------------------------------------------
run: $(OUTPUT)
	@echo $(OUTPUT)

install:
	cp  $(OUTPUT)$(EXEEXT) $(PREFIX)


DEBUGFLAGS	:=
UNAME := $(shell uname -s)
CFLAGS	:=	$(DEBUGFLAGS) -Wall -O3
CFLAGS	+=	$(INCLUDE)
LDFLAGS	=	$(DEBUGFLAGS)

ifneq (,$(findstring Darwin,$(UNAME)))
        LDFLAGS         +=
endif

ifneq (,$(findstring MINGW,$(UNAME)))
	PLATFORM	:= win32
	EXEEXT		:= .exe
	CFLAGS		+= -mno-cygwin
	LDFLAGS		+= -mno-cygwin -s
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
	CFLAGS		+= -mno-cygwin
	LDFLAGS		+= -mno-cygwin -s
	EXEEXT		:= .exe
endif

ifneq (,$(findstring Linux,$(UNAME)))
	LDFLAGS 	+= -static -s
endif

CXXFLAGS	=	$(CFLAGS) -fno-rtti -fno-exceptions

export OUTPUTDIR:=	$(CURDIR)
export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
			$(CURDIR)/DefaultArm7 $(CURDIR)/Loader
			
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)
			
#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))
BMPFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bmp)))
export OFILES	:= $(BINFILES:.bin=.o) $(BMPFILES:.bmp=.o)  $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
DEPENDS	:=	$(OFILES:.o=.d)

LINKABLE_OBJ :=	$(foreach obj,$(OFILES), $(CURDIR)/../$(obj))
LINKABLE_OBJD :=	$(foreach obj,$(OFILES), $(CURDIR)/../${obj:.o=.d})


#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------


#---------------------------------------------------------------------------------
# Compile Targets for C/C++
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
%.o : %.cpp
	@echo $(notdir $<)
	@g++ -MMD $(CXXFLAGS) $(INCLUDE)	-o ../$@ -c $<

#---------------------------------------------------------------------------------
%.o : %.c
	@echo $(notdir $<)
	@gcc -MMD $(CFLAGS) $(INCLUDE)	-o ../$@ -c $<

#---------------------------------------------------------------------------------
%.o : %.s
	@echo $(notdir $<)
	@as -MMD $(ASFLAGS) -o $@ -c $<


#---------------------------------------------------------------------------------
%.c	:	%.bmp
#---------------------------------------------------------------------------------
	-@$(BIN2C)	$<	${@:.bmp=.c}	${@:.c=}
	
#retry if new objects are found
#---------------------------------------------------------------------------------
%.c	:	%.bin
#---------------------------------------------------------------------------------
	-$(BIN2C)	$<	${@:.bin=.c}	${@:.c=}
	
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(TARGET): $(OFILES)
	@echo linking
	-g++ -v	-o $(TARGET)	$(LDFLAGS) $(LINKABLE_OBJ) 	$(LIBS)	$(INCLUDE)
	@./$(TARGET) -@ DefaultArm7/default_arm7.bin
