#ifndef FIELD_HPP
#define FIELD_HPP

// Standard headers
#include <iostream>
#include <memory>
#include <vector>

// Internal headers
#include "Dimension.hpp"
#include "Position.hpp"
#include "Player.hpp"

namespace rugby {

// Forward declaration
class Field;

// Aliases
using FieldPtr = std::shared_ptr<Field>;

// Classes

/**
 * A field is a 2D grid where a list of players play.
 */
class Field {
 public:
  // Constructors
  explicit Field(const dimension_t& dimension);

  // Concrete methods
  const dimension_t& dimension() const;

  std::ostream& print_info(std::ostream& out) const;
  std::ostream& print_grid(std::ostream& out) const;

  void add_player(const PlayerPtr& player, const position_t& position);
  void move_player(const PlayerPtr& player, const direction_t& direction);

 private:
  // Constants
  constexpr static dimension_t MIN_DIMENSION { 3, 3 };

  // Instance variables
  dimension_t _dimension;
  std::vector<std::vector<PlayerPtr>> _grid;

  // Concrete methods
  bool position_is_border(const position_t& p) const;
  bool position_is_beyond_border(const position_t& p) const;
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const Field& field);

}  // namespace rugby

#endif // FIELD_H
