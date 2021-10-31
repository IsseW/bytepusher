#include "grid.h"

#include <algorithm>
#include <iostream>

Grid::Grid(uint32_t width, uint32_t height) : width(width), height(height) {
  current_data = std::make_unique<Tile[]>(width * height);
  working_data = std::make_unique<Tile[]>(width * height);
}

void Grid::update_with_rule(void (*rule)(Grid&, uint32_t x, uint32_t y)) {
  for (uint32_t y = 0; y < height; y++) {
    for (uint32_t x = 0; x < width; x++) {
      rule(*this, x, y);
    }
  }
  swap();
}
void Grid::set_tile(size_t x, size_t y, Tile state) {
  current_data.get()[y * width + x] = state;
}
void Grid::print() {
  for (uint32_t y = 0; y < height; y++) {
    for (uint32_t x = 0; x < width; x++) {
      std::cout << (get(x, y) == Tile::Alive ? '#' : '.');
    }
    std::cout << std::endl;
  }
}

Tile Grid::get(uint32_t x, uint32_t y) {
  if (x >= width || y >= height) {
    return Tile::Dead;
  }
  return current_data.get()[y * width + x];
}
void Grid::set(uint32_t x, uint32_t y, Tile tile) {
  working_data.get()[y * width + x] = tile;
}

void Grid::swap() { std::swap(current_data, working_data); }

uint32_t Grid::count_neighbors(uint32_t x, uint32_t y, Tile to_count,
                               uint32_t extent) {
                                 
  uint32_t min_x = std::max<int32_t>(x - extent, 0);
  uint32_t max_x = std::min<int32_t>(x + extent, width - 1);
  uint32_t min_y = std::max<int32_t>(y - extent, 0);
  uint32_t max_y = std::min<int32_t>(y + extent, height - 1);

  uint32_t count = 0;
  for (uint32_t _y = min_y; _y <= max_y; _y++) {
    for (uint32_t _x = min_x; _x <= max_x; _x++) {
      if (_x == x && _y == y) {
        continue;
      }
      if (get(_x, _y) == to_count) {
        count++;
      }
    }
  }
  return count;
}