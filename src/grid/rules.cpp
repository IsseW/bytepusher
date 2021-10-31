#include "rules.h"

void game_of_life_rule(Grid& grid, uint32_t x, uint32_t y) {
  Tile tile = grid.get(x, y);
  uint32_t count = grid.count_neighbors(x, y);
  if (tile == Tile::Alive) {
    if (count < 2 || count > 3) {
      tile = Tile::Dead;
    }
  } else if (tile == Tile::Dead && count == 3) {
    tile = Tile::Alive;
  }
  grid.set(x, y, tile);
}

void water_sim_rule(Grid& grid, uint32_t x, uint32_t y) {
  Tile tile = grid.get(x, y);
  if (tile == Tile::Alive) {
    if (grid.get(x, y + 1) == Tile::Dead) {
      tile = Tile::Dead;
      grid.set(x, y + 1, Tile::Alive);
    } else if (grid.get(x + 1, y) == Tile::Dead && grid.get(x + 1, y + 1) == Tile::Dead) {
      tile = Tile::Dead;
      grid.set(x + 1, y + 1, Tile::Alive);
    } else if (grid.get(x - 1, y) == Tile::Dead && grid.get(x - 1, y + 1) == Tile::Dead) {
      tile = Tile::Dead;
      grid.set(x - 1, y + 1, Tile::Alive);
    }
  }
  grid.set(x, y, tile);
}