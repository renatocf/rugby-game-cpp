// C headers
#include <cassert>

// Standard headers
#include <stdexcept>
#include <utility>

// Internal headers
#include "Player.hpp"

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

Spy::Spy(PlayerPtr player)
  // std::move allows reusing a copy of an object
  // https://en.cppreference.com/w/cpp/utility/move
  : _player(std::move(player)),
    _number_uses(0) {
  if (_player == nullptr) {
    throw std::invalid_argument("Spy cannot receive a null pointer to Player");
  }
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

position_t Spy::player_position() {
  assert(_player != nullptr);
  _number_uses++;
  return _player->position();
}

/*----------------------------------------------------------------------------*/

size_t Spy::number_uses() const {
  return _number_uses;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
