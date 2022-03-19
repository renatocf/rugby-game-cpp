// C headers
#include <cassert>
#include <cstddef>

// Standard headers
#include <utility>
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

Game::Game(
    const dimension_t& field_dimension,
    size_t max_number_spies,
    PlayerStrategy execute_attacker_strategy,
    PlayerStrategy execute_defender_strategy)
    : _field(field_dimension),
      _max_number_spies(max_number_spies),
      // std::move allows reusing a copy of an object
      // https://en.cppreference.com/w/cpp/utility/move
      _execute_attacker_strategy(std::move(execute_attacker_strategy)),
      _execute_defender_strategy(std::move(execute_defender_strategy)),
      _attacker(std::make_shared<Player>('A')),
      _defender(std::make_shared<Player>('D')),
      _attacker_spy(_attacker),
      _defender_spy(_defender) {
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

    move_player(_execute_attacker_strategy, _attacker, _defender_spy);
    move_player(_execute_defender_strategy, _defender, _attacker_spy);

    out << *this;

    if (has_spy_exceeded_max_number_uses(_defender_spy)) {
      out << "GAME OVER! Attacker cheated spying more than "
          << _max_number_spies
          << (_max_number_spies == 1UL ? "time" : "times")
          << "!"
          << std::endl;
      return;
    }

    if (has_spy_exceeded_max_number_uses(_attacker_spy)) {
      out << "GAME OVER! Defender cheated spying more than "
          << _max_number_spies
          << " "
          << (_max_number_spies == 1UL ? "time" : "times")
          << "!"
          << std::endl;
      return;
    }

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

bool Game::has_spy_exceeded_max_number_uses(const Spy& opponent_spy) const {
  return opponent_spy.number_uses() > _max_number_spies;
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

void Game::move_player(const PlayerStrategy& execute_player_strategy,
                       const PlayerPtr& player,
                       Spy& opponent_spy) {
  assert(player != nullptr);

  direction_t player_direction =
    execute_player_strategy(player->position(), opponent_spy);

  _field.move_player(player, player_direction);
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
