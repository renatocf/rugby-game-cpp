#ifndef MAP_HPP
#define MAP_HPP

// Standard headers
#include <filesystem>
#include <fstream>
#include <vector>

// Internal headers
#include "Dimension.hpp"
#include "Position.hpp"

namespace rugby {

// Classes

/**
 * A map is 2D grid memory representation of the layout of a Game.
 */
class Map {
 public:
  // Constructors
  explicit Map(std::filesystem::path map_path);

  // Concrete methods
  const dimension_t& dimension() const;

  // Member operators
  char operator[](const position_t& position) const;

 private:
  // Aliases
  using Grid = std::vector<std::vector<char>>;

  // Instance variables
  dimension_t _dimension;
  Grid _grid;

  // Constructors
  explicit Map(std::ifstream map_file);

  // Static methods
  static std::ifstream make_ifstream_or_throw(std::filesystem::path map_path);
  static dimension_t read_dimension(std::istream& map_stream);
  static Grid read_grid(const dimension_t& dimension, std::istream& map_stream);
};

// Functions
std::ostream& operator<<(std::ostream& out, const Map& map);

}  // namespace rugby

#endif // MAP_HPP
