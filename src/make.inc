# This is the Makefile of Modules 

CXXFLAGS+= -I$(MODULES) -I$(GAME_INFO)


OBJS += $(MODULES)/prints.o

# Link all the other Makefiles 

include $(MODULES)/Cards/make.inc
include $(MODULES)/Gameplay/make.inc
include $(MODULES)/Phases/make.inc

#========|| E N D  O F  F I L E ||========