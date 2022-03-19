#ifndef FIELD_HPP
#define FIELD_HPP

// Standard headers
#include <iostream>
#include <memory>
#include <vector>

// Internal headers
#include "Dimension.hpp"
#include "Position.hpp"
#include "Item.hpp"

namespace rugby {

// Forward declaration
class Field;

// Aliases
using FieldPtr = std::shared_ptr<Field>;

// Classes

/**
 * A field is a 2D grid where a list of items play.
 */
class Field {
 public:
  // Constructors
  explicit Field(const dimension_t& dimension);

  // Concrete methods
  const dimension_t& dimension() const;

  std::ostream& print_info(std::ostream& out) const;
  std::ostream& print_grid(std::ostream& out) const;

  void add_item(const ItemPtr& item, const position_t& position);
  void move_item(const ItemPtr& item, const direction_t& direction);

 private:
  // Constants
  constexpr static dimension_t MIN_DIMENSION { 3, 3 };

  // Instance variables
  dimension_t _dimension;
  std::vector<std::vector<ItemPtr>> _grid;

  // Concrete methods
  bool position_is_beyond_limits(const position_t& p) const;
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const Field& field);

}  // namespace rugby

#endif // FIELD_H
