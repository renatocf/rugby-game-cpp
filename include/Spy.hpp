#ifndef SPY_HPP
#define SPY_HPP

// C headers
#include <cstddef>

// Internal headers
#include "Item.hpp"
#include "Position.hpp"

namespace rugby {

// Classes

/**
 * A spy allows retrieving the position of a item and counts
 * the number of accesses.
 */
class Spy {
 public:
  // Constructors
  explicit Spy(ItemPtr item);

  // Concrete methods
  position_t item_position();
  size_t number_uses() const;

 private:
  // Instance variables
  ItemPtr _item;
  size_t _number_uses;
};

}  // namespace rugby

#endif // SPY_HPP
