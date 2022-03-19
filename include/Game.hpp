#ifndef GAME_HPP
#define GAME_HPP

// C headers
#include <cstddef>

// Standard headers
#include <iostream>
#include <functional>

// Internal headers
#include "Dimension.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Spy.hpp"

namespace rugby {

// Aliases

/**
 * A player strategy is a function to determine the direction of a player
 * given its current position in a Field. Aditionally, players can spy
 * on its opponent positions **at most** MAX_NUMBER_SPIES times.
 */
using PlayerStrategy = std::function<direction_t(const position_t&, Spy&)>;

// Classes

/**
 * A game represents a field with two players: an attacker and a defender.
 * The attacker and the defender try to compete with each other.
 */
class Game {
 public:
  // Constructors
  Game(const dimension_t& field_dimension,
       size_t max_number_spies,
       PlayerStrategy execute_attacker_strategy,
       PlayerStrategy execute_defender_strategy);

  // Concrete methods
  void play(size_t max_turns, std::ostream& out = std::cout);

 private:
  // Instance variables
  Field _field;

  size_t _max_number_spies;

  PlayerStrategy _execute_attacker_strategy;
  PlayerStrategy _execute_defender_strategy;

  PlayerPtr _attacker;
  PlayerPtr _defender;

  Spy _attacker_spy;
  Spy _defender_spy;

  // Concrete methods
  void set_attacker_in_field();
  void set_defender_in_field();

  bool has_spy_exceeded_max_number_uses(const Spy& opponent_spy) const;
  bool has_defender_captured_attacker() const;
  bool has_attacker_arrived_end_field() const;

  void move_player(
      const PlayerStrategy& execute_player_strategy,
      const PlayerPtr& player,
      Spy& opponent_spy);

  // Friendship allows non-member functions to access
  // private fields inside a struct/class
  // https://en.cppreference.com/w/cpp/language/friend
  friend std::ostream& operator<<(std::ostream& out, const Game& game);
};

// Non-member operators
std::ostream& operator<<(std::ostream& out, const Game& game);

}  // namespace rugby

#endif // GAME_HPP
