#include <iostream>

#include "grid/grid.h"
#include "grid/rules.h"

int main(int argc, char* args[]) {
  Grid grid = Grid(10, 10);
  grid.set_tile(4, 4, Tile::Alive);
  grid.set_tile(4, 5, Tile::Alive);
  grid.set_tile(4, 6, Tile::Alive);
  for (uint32_t i = 0; i < 5; i++) {
    grid.print();
    std::cout << std::endl << "--------------------------" << std::endl;
    grid.update_with_rule(game_of_life_rule);
  }
  grid.print();
}