// Internal headers
#include "Direction.hpp"
#include "Position.hpp"
#include "Spy.hpp"

// Main header
#include "Defender.hpp"

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
direction_t execute_defender_strategy(
    const position_t& /* defender_position */, Spy& /* attacker_spy */) {

  // TODO: Implement Defender logic here
  return DIR::LEFT;
}

/*----------------------------------------------------------------------------*/

}  // namespace rugby
