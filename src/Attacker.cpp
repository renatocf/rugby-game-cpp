// Internal headers
#include "Direction.hpp"
#include "Position.hpp"
#include "Spy.hpp"

// Main header
#include "Attacker.hpp"

namespace rugby {

/* ////////////////////////////////////////////////////////////////////////// */
/* -------------------------------------------------------------------------- */
/*                                   PUBLIC                                   */
/* -------------------------------------------------------------------------- */
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */

/*----------------------------------------------------------------------------*/
/*                                  FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

// C++ compilers do not warn "unused parameter" if names are commented
direction_t execute_attacker_strategy(
    const position_t& /* attacker_position */, Spy& /* defender_spy */) {

  // TODO: Implement Attacker logic here
  return DIR::RIGHT;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
