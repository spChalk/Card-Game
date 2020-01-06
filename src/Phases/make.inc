# This is the Makefile of Phases

CXXFLAGS+= -I$(MODULES)/Phases

OBJS += $(MODULES)/Phases/battlePhase.o
OBJS += $(MODULES)/Phases/economyPhase.o
OBJS += $(MODULES)/Phases/equipPhase.o
OBJS += $(MODULES)/Phases/finalPhase.o
OBJS += $(MODULES)/Phases/startingPhase.o

#========|| E N D  O F  F I L E ||========