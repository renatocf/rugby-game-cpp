// C headers
#include <cassert>
#include <cstddef>

// Standard headers
#include <iostream>

// Main header
#include "Game.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Game::Game(const dimension_t& field_dimension)
    : _field(field_dimension),
      _attacker(std::make_shared<Player>('A')),
      _defender(std::make_shared<Player>('D')) {
  set_attacker_in_field();
  set_defender_in_field();
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

void Game::play(size_t max_turns, std::ostream& out) {
  out << "Turn 0\n";
  out << *this;

  for (size_t turn = 0; turn < max_turns; turn++) {
    out << "Turn " << turn + 1 << "\n";

    move_attacker();
    move_defender();

    out << *this;

    if (has_attacker_arrived_end_field()) {
      out << "GAME OVER! Attacker wins!" << std::endl;
      return;
    }

    if (has_defender_captured_attacker()) {
      out << "GAME OVER! Defender wins!" << std::endl;
      return;
    }
  }

  // A draw happens only if nobody wins before max_turns
  out << "GAME OVER! Attacker and Defender draw!" << std::endl;
}

/*----------------------------------------------------------------------------*/
/*                            NON-MEMBER OPERATORS                            */
/*----------------------------------------------------------------------------*/

std::ostream& operator<<(std::ostream& out, const Game& game) {
  out << game._field;
  return out;
}

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                  PRIVATE                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                             CONCRETE METHODS                               */
/*----------------------------------------------------------------------------*/

void Game::set_attacker_in_field() {
  assert(_attacker != nullptr);

  const auto& [ field_height, field_width ] = _field.dimension();

  position_t attacker_initial_position {
    field_height / 2, 1 // Left side of field
  };

  _field.add_player(_attacker, attacker_initial_position);
}

/*----------------------------------------------------------------------------*/

void Game::set_defender_in_field() {
  assert(_defender != nullptr);

  const auto& [ field_height, field_width ] = _field.dimension();

  position_t defender_initial_position = {
    field_height / 2, field_width - 2 // Right side of field
  };

  _field.add_player(_defender, defender_initial_position);
}

/*----------------------------------------------------------------------------*/

bool Game::has_defender_captured_attacker() const {
  assert(_defender != nullptr && _attacker != nullptr);
  return _defender->position().is_neighbor(_attacker->position());
}

/*----------------------------------------------------------------------------*/

bool Game::has_attacker_arrived_end_field() const {
  assert(_attacker != nullptr);
  return _attacker->position().j == _field.dimension().width - 2;
}

/*----------------------------------------------------------------------------*/

void Game::move_attacker() {
  // TODO: Implement Attacker logic here
  _field.move_player(_attacker, DIR::RIGHT);
}

/*----------------------------------------------------------------------------*/

void Game::move_defender() {
  // TODO: Implement Defender logic here
  _field.move_player(_defender, DIR::LEFT);
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
