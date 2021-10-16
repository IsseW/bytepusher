#include <algorithm>
#include <stdexcept>

enum class Tile : uint8_t {
  Dead,
  Alive,
};

struct Grid {
 private:
  uint32_t width;
  uint32_t height;
  Tile* current_data;
  Tile* working_data;

  Tile get(uint32_t x, uint32_t y) { return current_data[y * width + x]; }
  void set(uint32_t x, uint32_t y, Tile tile) {
    working_data[y * width + x] = tile;
  }

  void swap() { std::swap(current_data, working_data); }
  uint32_t count_neighbors(uint32_t x, uint32_t y, uint32_t extent = 1) {
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
        if (get(_x, _y) == Tile::Alive) {
          count++;
        }
      }
    }
    return count;
  }

 public:
  Grid(uint32_t width, uint32_t height) : width(width), height(height) {
    current_data = new Tile[width * height];
    working_data = new Tile[width * height];
  }

  void update_with_rule(Tile (*rule)(Tile, uint32_t), uint32_t extent = 1) {
    for (uint32_t y = 0; y < height; y++) {
      for (uint32_t x = 0; x < width; x++) {
        set(x, y, rule(get(x, y), count_neighbors(x, y)));
      }
    }
    swap();
  }

  ~Grid() {
    delete[] current_data;
    delete[] working_data;
  }
};