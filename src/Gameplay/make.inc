# This is the Makefile of Gameplay

CXXFLAGS+= -I$(MODULES)/Gameplay

OBJS += $(MODULES)/Gameplay/game.o
OBJS += $(MODULES)/Gameplay/player.o

#========|| E N D  O F  F I L E ||========