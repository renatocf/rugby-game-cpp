#ifndef DEFENDER_HPP
#define DEFENDER_HPP

// Internal headers
#include "Position.hpp"
#include "Spy.hpp"

namespace rugby {

// Functions

/**
 * Main algorithm to move Defender player in a Game.
 * Given the player position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_defender_strategy(const position_t& defender_position,
                                      Spy& attacker_spy);

}  // namespace rugby

#endif // DEFENDER_HPP
