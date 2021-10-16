#include <iostream>

#include "grid/grid.h"
int main() {
  Grid grid = Grid(10, 10);
  grid.set_tile(4, 4, Tile::Alive);
  grid.set_tile(4, 5, Tile::Alive);
  grid.set_tile(4, 6, Tile::Alive);
  for (uint32_t i = 0; i < 5; i++) {
    grid.print();
    std::cout << std::endl << "--------------------------" << std::endl;
    grid.update_with_rule([](Tile tile, uint32_t count) {
      if (tile == Tile::Alive) {
        if (count < 2 || count > 3) {
          return Tile::Dead;
        }
      } else if (count == 3) {
        return Tile::Alive;
      }
      return tile;
    });
  }
  grid.print();
}