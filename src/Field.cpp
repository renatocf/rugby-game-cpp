// C Headers
#include <cassert>

// Standard exceptions
#include <sstream>
#include <stdexcept>

// Internal headers
#include "Dimension.hpp"
#include "Position.hpp"

// Main header
#include "Field.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                CONSTRUCTORS                                */
/*----------------------------------------------------------------------------*/

Field::Field(const dimension_t& dimension)
    : _dimension(dimension),
      _grid(dimension.height, std::vector<PlayerPtr>(dimension.width)) {
  if (_dimension < Field::MIN_DIMENSION) {
    std::stringstream message_template;

    message_template
      << "Dimension must be at least ("
      << Field::MIN_DIMENSION
      << ") because of the Field's borders";

    throw std::invalid_argument(message_template.str());
  }
}

/*----------------------------------------------------------------------------*/
/*                             CONCRETE METHODS                               */
/*----------------------------------------------------------------------------*/

const dimension_t& Field::dimension() const {
  return _dimension;
}

/*----------------------------------------------------------------------------*/

std::ostream& Field::print_info(std::ostream& out) const {
  out << "Dimensions (H x W)"
      << _dimension.height << " x " << _dimension.width
      << std::endl;

  return out;
}

/*----------------------------------------------------------------------------*/

std::ostream& Field::print_grid(std::ostream& out) const {
  for (size_t i = 0; i < _dimension.height; i++) {
    for (size_t j = 0; j < _dimension.width; j++) {
      out << '|';
      if (position_is_border({ i, j }))
        out << 'X';
      else
        out << _grid[i][j];
    }
    out << '|';
    out << std::endl;
  }
  out << std::endl;

  return out;
}

/*----------------------------------------------------------------------------*/

void Field::add_player(const PlayerPtr& player, const position_t& position) {
  if (player == nullptr) return;

  if (position_is_beyond_border(position)) {
    std::stringstream message_template;

    message_template
      << "Player " << player << "must be within the borders of the field!";

    throw std::out_of_range(message_template.str());
  }

  _grid[position.i][position.j] = player;
  player->position(position);
}

/*----------------------------------------------------------------------------*/

void Field::move_player(const PlayerPtr& player, const direction_t& direction) {
  if (player == nullptr) return;

  position_t player_position = player->position();

  // Given how players are added to the field, their position
  // should never be in the border of the field
  assert(!position_is_border(player->position()));

  position_t new_position = player->position().calculate_move(direction);

  // Player cannot be moved if position is already occupied
  if (position_is_border(new_position)) return;

  // Change current position in the grid
  _grid[new_position.i][new_position.j] = player;
  _grid[player_position.i][player_position.j] = nullptr;
  player->position(new_position);
}

/*----------------------------------------------------------------------------*/
/*                            NON-MEMBER OPERATORS                            */
/*----------------------------------------------------------------------------*/

std::ostream& operator<<(std::ostream& out, const Field& field) {
  field.print_grid(out);
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

bool Field::position_is_border(const position_t& p) const {
  return p.i == 0 || p.j == 0
    || p.i == _dimension.height-1 || p.j == _dimension.width-1;
}

/*----------------------------------------------------------------------------*/

bool Field::position_is_beyond_border(const position_t& p) const {
  return p.i == 0 || p.j == 0
    || p.i > _dimension.height-1 || p.j > _dimension.width-1;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
