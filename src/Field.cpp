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
      _grid(dimension.height, std::vector<ItemPtr>(dimension.width)) {
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
      out << _grid[i][j];
    }
    out << '|';
    out << std::endl;
  }
  out << std::endl;

  return out;
}

/*----------------------------------------------------------------------------*/

void Field::add_item(const ItemPtr& item, const position_t& position) {
  if (item == nullptr) return;

  if (position_is_beyond_limits(position)) {
    std::stringstream message_template;

    message_template
      << "Item " << item << "must be within the limits of the field!";

    throw std::out_of_range(message_template.str());
  }

  _grid[position.i][position.j] = item;
  item->position(position);
}

/*----------------------------------------------------------------------------*/

void Field::move_item(const ItemPtr& item, const direction_t& direction) {
  if (item == nullptr) return;

  position_t item_position = item->position();

  // Given how items are added to the field, their position
  // should never be in the border of the field
  assert(!position_is_beyond_limits(item->position()));

  if (!item->is_movable()) {
    throw std::logic_error(
        "Should not try to move an item that is not movable");
  }

  position_t new_position = item->position().calculate_move(direction);

  // Change current position in the grid
  _grid[new_position.i][new_position.j] = item;
  _grid[item_position.i][item_position.j] = nullptr;
  item->position(new_position);
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

bool Field::position_is_beyond_limits(const position_t& p) const {
  return p.i > _dimension.height-1 || p.j > _dimension.width-1;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
