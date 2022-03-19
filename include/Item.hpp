#ifndef PLAYER_HPP
#define PLAYER_HPP

// Standard headers
#include <memory>

// Internal headers
#include "Position.hpp"

namespace rugby {

// Forward declaration
class Item;

// Aliases
using ItemPtr = std::shared_ptr<Item>;

// Classes

/**
 * A item is represented by a symbol and its current position in a field.
 */
class Item {
 public:
  // Constructors
  explicit Item(char symbol, bool is_movable);

  // Concrete methods
  char symbol() const;
  bool is_movable() const;
  const position_t& position() const;
  void position(const position_t& new_position);

 private:
  // Instance variables
  char _symbol;
  bool _is_movable;
  position_t _position;
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const Item& item);
std::ostream& operator<<(std::ostream& out, const ItemPtr& item_ptr);

}  // namespace rugby

#endif // PLAYER_HPP
