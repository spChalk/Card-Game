# This is the Makefile of cardGame

MODULES = ./src
GAME_INFO = ./files

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11

PROGRAM = cardGame

OBJS = main.o

include $(MODULES)/make.inc		# Include other Makefiles

$(PROGRAM):	 clean $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

check: $(PROGRAM)		# Command to check for memory leaks
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROGRAM)

clean:
	@rm -f $(PROGRAM) $(OBJS)