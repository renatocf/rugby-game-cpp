// C headers
#include <cstddef>
#include <cstdlib>

// Standard headers
#include <iostream>

// Internal headers
#include "Attacker.hpp"
#include "Defender.hpp"
#include "Dimension.hpp"
#include "Game.hpp"

// Constants
const rugby::dimension_t STANDARD_FIELD_DIMENSION { 10, 10 };
const size_t STANDARD_MAX_NUMBER_SPIES { 1 };
const size_t STANDARD_MAX_TURNS { 42 };

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main() {
  std::cout << "Hello, Rugby!\n" << std::endl;

  rugby::Game game(
      STANDARD_FIELD_DIMENSION,
      STANDARD_MAX_NUMBER_SPIES,
      rugby::execute_attacker_strategy,
      rugby::execute_defender_strategy);

  game.play(STANDARD_MAX_TURNS);

  return EXIT_SUCCESS;
}
