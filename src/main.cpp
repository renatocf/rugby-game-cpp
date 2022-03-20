// C headers
#include <cassert>
#include <cstddef>
#include <cstdlib>

// Standard headers
#include <iostream>
#include <filesystem>
#include <utility>

// Internal headers
#include "Attacker.hpp"
#include "Defender.hpp"
#include "Dimension.hpp"
#include "Map.hpp"
#include "Game.hpp"

// Constants
const rugby::dimension_t STANDARD_FIELD_DIMENSION { 10, 10 };
const size_t STANDARD_MAX_NUMBER_SPIES { 1 };
const size_t STANDARD_MAX_TURNS { 42 };

/*----------------------------------------------------------------------------*/
/*                       AUXILIARY FUNCTIONS DECLARATION                      */
/*----------------------------------------------------------------------------*/

rugby::Game choose_game(int argc, char** argv);
rugby::Game make_standard_game();
rugby::Game make_game_from_map(std::filesystem::path map_path);

/*----------------------------------------------------------------------------*/
/*                               MAIN FUNCTION                                */
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
  if (argc >= 3) {
    std::cerr << "USAGE: " << argv[0] << " [map_path]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Hello, Rugby!\n" << std::endl;

  rugby::Game game = choose_game(argc, argv);
  game.play(STANDARD_MAX_TURNS);

  return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*                             AUXILIARY FUNCTIONS                            */
/*----------------------------------------------------------------------------*/

rugby::Game choose_game(int argc, char** argv) {
  switch (argc) {
    case 1: return make_standard_game();
    case 2: return make_game_from_map(argv[1]);
    default:
      // argc should not be any other number
      assert(false);
  }
}

/*----------------------------------------------------------------------------*/

rugby::Game make_standard_game() {
  return {
    STANDARD_FIELD_DIMENSION,
    STANDARD_MAX_NUMBER_SPIES,
    rugby::execute_attacker_strategy,
    rugby::execute_defender_strategy
  };
}

/*----------------------------------------------------------------------------*/

rugby::Game make_game_from_map(std::filesystem::path map_path) {
  // std::move allows reusing a copy of an object
  // https://en.cppreference.com/w/cpp/utility/move
  rugby::Map map(std::move(map_path));

  return {
    map,
    STANDARD_MAX_NUMBER_SPIES,
    rugby::execute_attacker_strategy,
    rugby::execute_defender_strategy
  };
}

/*----------------------------------------------------------------------------*/
