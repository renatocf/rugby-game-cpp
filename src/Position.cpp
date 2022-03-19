// C headers
#include <cstddef>

// Main header
#include "Position.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                             CONCRETE METHODS                               */
/*----------------------------------------------------------------------------*/

bool position_t::is_neighbor(const position_t& candidate) const {
  return candidate.i >= this->i-1 && candidate.i <= this->i+1
    && candidate.j >= this->i-1 && candidate.j <= this->j+1;
}

/*----------------------------------------------------------------------------*/

position_t position_t::calculate_move(const direction_t& direction) const {
  return { this->i + direction.i, this->j + direction.j };
}

/*----------------------------------------------------------------------------*/
/*                            NON-MEMBER OPERATORS                            */
/*----------------------------------------------------------------------------*/

std::ostream& operator<<(std::ostream& out, const position_t& position) {
  out << position.i << "," << position.j;

  return out;
}

/*----------------------------------------------------------------------------*/

std::istream& operator>>(std::istream& in, position_t& position) {
  char comma;

  in >> position.i;
  in >> comma;
  in >> position.j;

  return in;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
