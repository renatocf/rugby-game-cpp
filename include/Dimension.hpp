#ifndef DIMENSION_HPP
#define DIMENSION_HPP

// C headers
#include <cstddef>

// Standard headers
#include <compare>
#include <iostream>

namespace rugby {

// Structs

/**
 * A dimension represents the number of lines and columns in a 2D grid.
 */
struct dimension_t {
 public:
  // Instance variables
  size_t height;
  size_t width;

  // Member operators

  // Operator Spaceship is a three-way comparison between instances
  // of the same type. It allows generating the other six comparison
  // operators (==, !=, <, <=, >, >=) automatically.
  // https://en.cppreference.com/w/cpp/language/default_comparisons
  constexpr auto operator<=>(const dimension_t& dimension) const = default;
};

// Constants
constexpr dimension_t NULL_DIMENSION { 0, 0 };

// Non-member operators
std::ostream& operator<<(std::ostream& out, const dimension_t& dimension);
std::istream& operator>>(std::istream& in, dimension_t& dimension);

}  // namespace rugby

#endif // DIMENSION_HPP
