#pragma once
#include <memory>
enum class Tile : uint8_t {
  Dead = 0x0,
  Other = 0b000011,
  Alive = 0xFF,
};

struct Grid {
 private:
  uint32_t width;
  uint32_t height;
  std::unique_ptr<uint8_t[]> current_data;
  std::unique_ptr<uint8_t[]> working_data;

  void swap();

 public:
  // Count how many neighbours have the state of to_count. 
  // Counts with x and y as center and with extent
  uint32_t count_neighbors(uint32_t x, uint32_t y, Tile to_count = Tile::Alive,
                           uint32_t extent = 1);
  // Get tile in the current data
  Tile get(uint32_t x, uint32_t y);

  // Set tile on the working data
  void set(uint32_t x, uint32_t y, Tile tile);
  // Set tile in current data. Do not use in rule.
  void set_tile(size_t x, size_t y, Tile state);

  // Print the grid to stdout
  void print();

  Grid(uint32_t width, uint32_t height);

  void update_with_rule(void (*rule)(Grid&, uint32_t x, uint32_t y));

  const uint8_t* get_texture();
};