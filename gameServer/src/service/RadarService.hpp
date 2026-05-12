#ifndef battleship_game_RadarService_hpp
#define battleship_game_RadarService_hpp

#include "dto/RadarDto.hpp"
#include <string>
#include <vector>

namespace battleship { namespace game { namespace service {

class RadarService {
private:
  // One charge per player per game
  bool m_p1Used = false;
  bool m_p2Used = false;

public:
  void reset();

  oatpp::Object<RadarResponseDto> scan(
    int player,
    int centerRow,
    int centerCol,
    const std::vector<std::string>& opponentBoard) const;

  // Returns true if the player still has their radar charge
  bool hasCharge(int player) const;

  // Consume the charge for a player after a successful scan
  void useCharge(int player);
};

}}}

#endif
