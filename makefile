
CXX = g++
CFLAGS = -O0 -Wall
CLIBS = 

INCLUDE = include
SOURCE = src/main.cpp
OUT = app

build:
	$(CXX) $(CFLAGS) -o $(OUT) -I $(INCLUDE) $(SOURCE)