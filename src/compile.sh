#!/bin/bash
#set -x
g++ -o play -I. -I./Phases/ -I./Gameplay -I./Cards ./Cards/*.cpp ./Gameplay/*.cpp ./Phases/*.cpp ./*.cpp ../main.cpp