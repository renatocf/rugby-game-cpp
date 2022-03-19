#ifndef POSITION_HPP
#define POSITION_HPP

// C headers
#include <cstddef>

// Standard headers
#include <compare>
#include <iostream>
#include <limits>

// Internal headers
#include "Direction.hpp"

namespace rugby {

// Structs

/**
 * A position represents where an object is in a 2D grid.
 */
struct position_t {
 public:
  // Public instance variables
  size_t i;
  size_t j;

  // Public concrete methods
  bool is_neighbor(const position_t& candidate) const;
  position_t calculate_move(const direction_t& direction) const;

  // Member operators

  // Operator Spaceship is a three-way comparison between instances
  // of the same type. It allows generating the other six comparison
  // operators (==, !=, <, <=, >, >=) automatically.
  // https://en.cppreference.com/w/cpp/language/default_comparisons
  constexpr auto operator<=>(const position_t& position) const = default;
};

// Constants
constexpr position_t INVALID_POSITION {
  std::numeric_limits<size_t>::max(),
  std::numeric_limits<size_t>::max(),
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const position_t& position);
std::istream& operator>>(std::istream& in, position_t& position);

}  // namespace rugby

#endif // POSITION_H
