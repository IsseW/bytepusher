#include "rules.h"

void game_of_life_rule(Grid& grid, uint32_t x, uint32_t y) {
  Tile tile = grid.get(x, y);
  uint32_t count = grid.count_neighbors(x, y);
  if (tile == Tile::Alive) {
    if (count < 2 || count > 3) {
      tile = Tile::Dead;
    }
  } else if (count == 3) {
    tile = Tile::Alive;
  }
  grid.set(x, y, tile);
}

void water_sim_rule(Grid& grid, uint32_t x, uint32_t y) {
  Tile tile = grid.get(x, y);
  grid.set(x, y, tile);
}