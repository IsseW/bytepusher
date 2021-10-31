CXX 		= g++
CFLAGS 		= -O0 -Wall
CLIBS 		=-lSDL2

INCLUDE 	= src
SOURCE 		= src/main.cpp src/grid/grid.cpp src/grid/rules.cpp src/renderer/renderer.cpp
OUT 		= app

build:
	$(CXX) $(CLIBS) $(CFLAGS) -o $(OUT) -I $(INCLUDE) $(SOURCE)