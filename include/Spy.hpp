#ifndef SPY_HPP
#define SPY_HPP

// C headers
#include <cstddef>

// Internal headers
#include "Player.hpp"
#include "Position.hpp"

namespace rugby {

// Classes

/**
 * A spy allows retrieving the position of a player and counts
 * the number of accesses.
 */
class Spy {
 public:
  // Constructors
  explicit Spy(PlayerPtr player);

  // Concrete methods
  position_t player_position();
  size_t number_uses() const;

 private:
  // Instance variables
  PlayerPtr _player;
  size_t _number_uses;
};

}  // namespace rugby

#endif // SPY_HPP
