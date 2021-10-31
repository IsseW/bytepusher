CXX 		= g++
CFLAGS 		= -O0 -Wall -g
CLIBS 		=-lSDL2

INCLUDE 	= src
SOURCE 		= src/main.cpp src/grid/grid.cpp src/grid/rules.cpp src/renderer/renderer.cpp
OUT 		= app

PHONY = build gitcommit gitpush gitpull

build:
	$(CXX) $(CLIBS) $(CFLAGS) -o $(OUT) -I $(INCLUDE) $(SOURCE)

gitcommit:
	git commit -a
gitpush:
	git push
gitpull:
	git pull