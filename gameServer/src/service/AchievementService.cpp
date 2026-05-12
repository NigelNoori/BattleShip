#include "AchievementService.hpp"

namespace battleship { namespace game { namespace service {

oatpp::Object<AchievementDto> AchievementService::evaluate(
    int winner,
    int rounds,
    int shipsDestroyed,
    int totalEnemyShips) const {

  auto result           = AchievementDto::createShared();
  result->player        = winner;
  result->rounds        = rounds;

  // Hot Shot: win in under 20 rounds
  result->hotShot       = (rounds < 20);

  // Perfect Victory: sank every single enemy ship
  result->perfectVictory = (totalEnemyShips > 0 &&
                            shipsDestroyed >= totalEnemyShips);

  return result;
}

}}}
