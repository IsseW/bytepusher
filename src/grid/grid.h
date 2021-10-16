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
  std::unique_ptr<Tile[]> current_data;
  std::unique_ptr<Tile[]> working_data;

  void swap();

 public:
  uint32_t count_neighbors(uint32_t x, uint32_t y, Tile to_count = Tile::Alive,
                           uint32_t extent = 1);
  Tile get(uint32_t x, uint32_t y);
  // Set tile on the working data
  void set(uint32_t x, uint32_t y, Tile tile);

  // Set tile in current data. Do not use in rule.
  void set_tile(size_t x, size_t y, Tile state);
  void print();
  Grid(uint32_t width, uint32_t height);

  void update_with_rule(void (*rule)(Grid&, uint32_t x, uint32_t y));
};