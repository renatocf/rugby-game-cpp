// Standard headers
#include <cassert>

// Standard headers
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

// Internal headers
#include "Dimension.hpp"

// Main header
#include "Map.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Map::Map(std::filesystem::path map_path)
    : Map(make_ifstream_or_throw(std::move(map_path))) {
}

/*----------------------------------------------------------------------------*/
/*                             CONCRETE METHODS                               */
/*----------------------------------------------------------------------------*/

const dimension_t& Map::dimension() const {
  return _dimension;
}

/*----------------------------------------------------------------------------*/
/*                              MEMBER OPERATORS                              */
/*----------------------------------------------------------------------------*/

char Map::operator[](const position_t& position) const {
  return _grid[position.i][position.j];
}

/*----------------------------------------------------------------------------*/
/*                            NON-MEMBER OPERATORS                            */
/*----------------------------------------------------------------------------*/

std::ostream& operator<<(std::ostream& out, const Map& map) {
  const auto& [ map_height, map_width ] = map.dimension();

  for (size_t i = 0; i < map_height; i++) {
    for (size_t j = 0; j < map_width; j++) {
      out << map[{ i, j }];
    }
    out << '\n';
  }
  out << std::endl;

  return out;
}

/*----------------------------------------------------------------------------*/

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                  PRIVATE                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Map::Map(std::ifstream map_file)
    : _dimension(read_dimension(map_file)),
      _grid(read_grid(_dimension, map_file)) {
}

/*----------------------------------------------------------------------------*/
/*                              STATIC METHODS                               */
/*----------------------------------------------------------------------------*/

std::ifstream Map::make_ifstream_or_throw(std::filesystem::path map_path) {
  std::ifstream map_file(map_path);

  if (map_file.fail()) {
    std::stringstream message_template;

    message_template
      << "Could not open file" << map_path;

    throw std::runtime_error(message_template.str());
  }

  return map_path;
}

/*----------------------------------------------------------------------------*/

dimension_t Map::read_dimension(std::istream& map_stream) {
  dimension_t dimension;
  map_stream >> dimension;

  // Ignores single character (newline)
  // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
  map_stream.ignore();

  if (map_stream.fail()) {
    throw std::runtime_error("Map dimension not specified");
  }

  return dimension;
}

/*----------------------------------------------------------------------------*/

Map::Grid Map::read_grid(const dimension_t& dimension,
                         std::istream& map_stream) {
  Grid grid(dimension.height, std::vector<char>(dimension.width));

  std::string buffer;
  size_t line = 0;

  for (line = 0; std::getline(map_stream, buffer, '\n'); line++) {
    // Warns if there are less columns than width
    if (buffer.size() < dimension.width) {
      std::cerr
        << "Line " << line
        << " does not have at least " << dimension.width
        << " columns" << std::endl;
    }

    // Warns if there are more columns than width
    if (buffer.size() > dimension.width) {
      std::cerr
        << "Line " << line
        << " has more than " << dimension.width
        << " columns" << std::endl;
    }

    size_t max_column = std::min(dimension.width, buffer.size());

    for (size_t column = 0; column < max_column; column++) {
      grid[line][column] = buffer[column];
    }
  }

  // Warns if there are less lines than height
  if (line < dimension.height) {
      std::cerr
        << "Map does not have at least " << dimension.height
        << " lines" << std::endl;
  }

  return grid;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
