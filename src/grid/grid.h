#include <memory>
enum class Tile : uint8_t {
  Dead,
  Alive,
};

struct Grid {
 private:
  uint32_t width;
  uint32_t height;
  std::unique_ptr<Tile[]> current_data;
  std::unique_ptr<Tile[]> working_data;

  Tile get(uint32_t x, uint32_t y);
  void set(uint32_t x, uint32_t y, Tile tile);

  void swap();
  uint32_t count_neighbors(uint32_t x, uint32_t y, uint32_t extent = 1);

 public:
  void set_tile(size_t x, size_t y, Tile state);
  void print();
  Grid(uint32_t width, uint32_t height);

  void update_with_rule(Tile (*rule)(Tile, uint32_t), uint32_t extent = 1);
};