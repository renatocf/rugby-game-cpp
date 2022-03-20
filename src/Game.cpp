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
    : Game(field_dimension,
           max_number_spies,
           std::move(execute_attacker_strategy),
           std::move(execute_defender_strategy),
           nullptr) {
  set_attacker_in_field();
  set_defender_in_field();
  set_obstacles_in_field();
}

/*----------------------------------------------------------------------------*/

Game::Game(
    const Map& map,
    size_t max_number_spies,
    PlayerStrategy execute_attacker_strategy,
    PlayerStrategy execute_defender_strategy)
    : Game(map.dimension(),
           max_number_spies,
           std::move(execute_attacker_strategy),
           std::move(execute_defender_strategy),
           nullptr) {
  if (has_map_exceeded_max_occurrences_of_symbol(
        map, _attacker->symbol(), Game::MAX_SINGLE_OCCURRENCE)) {
    std::stringstream message_template;

    message_template
      << "Map exceeded max occurrences of symbol " << _attacker->symbol();

    throw std::runtime_error(message_template.str());
  }

  if (has_map_exceeded_max_occurrences_of_symbol(
        map, _defender->symbol(), Game::MAX_SINGLE_OCCURRENCE)) {
    std::stringstream message_template;

    message_template
      << "Map exceeded max occurrences of symbol " << _attacker->symbol();

    throw std::runtime_error(message_template.str());
  }

  set_item_in_field_from_map(_attacker, map);
  set_item_in_field_from_map(_defender, map);
  set_item_in_field_from_map(_obstacle, map);
}

/*----------------------------------------------------------------------------*/
/*                              CONCRETE METHODS                              */
/*----------------------------------------------------------------------------*/

void Game::play(size_t max_turns, std::ostream& out) {
  out << "Turn 0\n";
  out << *this;

  for (size_t turn = 0; turn < max_turns; turn++) {
    out << "Turn " << turn + 1 << "\n";

    move_item(_execute_attacker_strategy, _attacker, _defender_spy);
    move_item(_execute_defender_strategy, _defender, _attacker_spy);

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
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Game::Game(
    const dimension_t& field_dimension,
    size_t max_number_spies,
    PlayerStrategy execute_attacker_strategy,
    PlayerStrategy execute_defender_strategy,
    void* /* dummy */)
    : _field(field_dimension),
      _max_number_spies(max_number_spies),
      // std::move allows reusing a copy of an object
      // https://en.cppreference.com/w/cpp/utility/move
      _execute_attacker_strategy(std::move(execute_attacker_strategy)),
      _execute_defender_strategy(std::move(execute_defender_strategy)),
      _attacker(std::make_shared<Item>('A', true)),
      _defender(std::make_shared<Item>('D', true)),
      _obstacle(std::make_shared<Item>('X', false)),
      _attacker_spy(_attacker),
      _defender_spy(_defender) {
}

/*----------------------------------------------------------------------------*/
/*                             CONCRETE METHODS                               */
/*----------------------------------------------------------------------------*/

bool Game::has_map_exceeded_max_occurrences_of_symbol(
    const Map& map, char symbol, size_t max_occurrences) {
  if (max_occurrences == 0) return false;

  const auto& [ map_height, map_width ] = map.dimension();

  size_t item_symbol_occurrences = 0;
  for (size_t i = 0; i < map_height; i++) {
    for (size_t j = 0; j < map_width; j++) {
      if (map[{ i, j }] == symbol) {
        item_symbol_occurrences++;
      }
    }
  }

  return item_symbol_occurrences > max_occurrences;
}

/*----------------------------------------------------------------------------*/

void Game::set_item_in_field_from_map(const ItemPtr& item, const Map& map) {
  // By design, field should have the same dimension as the map
  assert(_field.dimension() == map.dimension());

  const auto& [ map_height, map_width ] = map.dimension();

  for (size_t i = 0; i < map_height; i++) {
    for (size_t j = 0; j < map_width; j++) {
      if (map[{ i, j }] == item->symbol()) {
        _field.add_item(item, { i, j });
      }
    }
  }
}

/*----------------------------------------------------------------------------*/

void Game::set_attacker_in_field() {
  assert(_attacker != nullptr);

  const auto& [ field_height, field_width ] = _field.dimension();

  position_t attacker_initial_position {
    field_height / 2, 1 // Left side of field
  };

  _field.add_item(_attacker, attacker_initial_position);
}

/*----------------------------------------------------------------------------*/

void Game::set_defender_in_field() {
  assert(_defender != nullptr);

  const auto& [ field_height, field_width ] = _field.dimension();

  position_t defender_initial_position = {
    field_height / 2, field_width - 2 // Right side of field
  };

  _field.add_item(_defender, defender_initial_position);
}

/*----------------------------------------------------------------------------*/

void Game::set_obstacles_in_field() {
  const auto& [ field_height, field_width ] = _field.dimension();

  for (size_t i = 0; i < field_height; i++) {
    _field.add_item(_obstacle, { i, 0 });
  }

  for (size_t i = 0; i < field_height; i++) {
    _field.add_item(_obstacle, { i, field_width-1 });
  }

  for (size_t j = 0; j < field_width; j++) {
    _field.add_item(_obstacle, { 0, j });
  }

  for (size_t j = 0; j < field_width; j++) {
    _field.add_item(_obstacle, { field_height-1, j });
  }
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

void Game::move_item(const PlayerStrategy& execute_item_strategy,
                     const ItemPtr& item,
                     Spy& opponent_spy) {
  assert(item != nullptr);

  direction_t item_direction =
    execute_item_strategy(item->position(), opponent_spy);

  _field.move_item(item, item_direction);
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
