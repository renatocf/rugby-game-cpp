#ifndef PLAYER_HPP
#define PLAYER_HPP

// Standard headers
#include <memory>

// Internal headers
#include "Position.hpp"

namespace rugby {

// Forward declaration
class Player;

// Aliases
using PlayerPtr = std::shared_ptr<Player>;

// Classes

/**
 * A player is represented by a symbol and its current position in a field.
 */
class Player {
 public:
  // Constructors
  explicit Player(char symbol);

  // Concrete methods
  char symbol() const;
  const position_t& position() const;
  void position(const position_t& new_position);

 private:
  // Instance variables
  char _symbol;
  position_t _position;
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const Player& player);
std::ostream& operator<<(std::ostream& out, const PlayerPtr& player_ptr);

}  // namespace rugby

#endif // PLAYER_HPP
