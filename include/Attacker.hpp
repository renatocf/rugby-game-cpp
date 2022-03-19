#ifndef ATTACKER_HPP
#define ATTACKER_HPP

// Internal headers
#include "Position.hpp"
#include "Spy.hpp"

namespace rugby {

// Functions

/**
 * Main algorithm to move Attacker item in a Game.
 * Given the item position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_attacker_strategy(const position_t& attacker_position,
                                      Spy& defender_spy);

}  // namespace rugby

#endif // ATTACKER_HPP
