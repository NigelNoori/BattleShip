#ifndef battleship_game_AchievementService_hpp
#define battleship_game_AchievementService_hpp

#include "dto/AchievementDto.hpp"

namespace battleship { namespace game { namespace service {

class AchievementService {
public:
  // Evaluate achievements for the winner given game stats
  // rounds       = total rounds played
  // shipsDestroyed = how many enemy ships the winner sank
  // totalEnemyShips = total ships the enemy placed
  oatpp::Object<AchievementDto> evaluate(
    int winner,
    int rounds,
    int shipsDestroyed,
    int totalEnemyShips) const;
};

}}}

#endif
