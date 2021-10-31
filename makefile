CXX 		= g++
CFLAGS 		= -O0 -Wall -g
CLIBS 		=-lSDL2

INCLUDE 	= src
SOURCE 		= src/main.cpp src/grid/grid.cpp src/grid/rules.cpp src/renderer/renderer.cpp
OUT 		= app

build:
	$(CXX) $(CFLAGS) $(CLIBS) -o $(OUT) -I $(INCLUDE) $(SOURCE)