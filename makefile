CXX 		= g++
CFLAGS 		= -O0 -Wall -g
CLIBS 		=-lSDL2

INCLUDE 	= src
SRC_FOLDER	= src
BIN_FOLDER  = build
SOURCE		= src/main.cpp src/grid/grid.cpp src/grid/rules.cpp src/renderer/renderer.cpp
OBJECTS		= $(SOURCE:$(SRC_FOLDER)/%.cpp=$(BIN_FOLDER)/%.o)
OUT 		= $(BIN_FOLDER)/app

PHONY 		= build gitcommit gitpush gitpull run

build: $(OUT)

$(BIN_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CLIBS) $(CFLAGS) -I$(INCLUDE) -c $< -o $@ 

$(OUT): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CLIBS) $(CFLAGS) -I$(INCLUDE) $^ -o $@

clean:
	rm -rf $(BIN_FOLDER)

run: build
	$(OUT)


gitcommit:
	git commit -a
gitpush:
	git push
gitpull:
	git pull
