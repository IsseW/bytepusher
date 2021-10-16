
CXX = g++
CFLAGS = -O0 -Wall
CLIBS = 

INCLUDE = src
SOURCE = src/main.cpp src/grid/grid.cpp src/grid/rules.cpp
OUT = app

build:
	$(CXX) $(CFLAGS) -o $(OUT) -I $(INCLUDE) $(SOURCE)