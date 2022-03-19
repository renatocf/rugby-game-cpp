// C headers
#include <cassert>

// Standard headers
#include <stdexcept>
#include <utility>

// Internal headers
#include "Item.hpp"

// Main header
#include "Spy.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Spy::Spy(ItemPtr item)
  // std::move allows reusing a copy of an object
  // https://en.cppreference.com/w/cpp/utility/move
  : _item(std::move(item)),
    _number_uses(0) {
  if (_item == nullptr) {
    throw std::invalid_argument("Spy cannot receive a null pointer to Item");
  }
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

position_t Spy::item_position() {
  assert(_item != nullptr);
  _number_uses++;
  return _item->position();
}

/*----------------------------------------------------------------------------*/

size_t Spy::number_uses() const {
  return _number_uses;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
