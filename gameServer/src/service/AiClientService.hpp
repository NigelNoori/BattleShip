#ifndef battleship_game_AiClientService_hpp
#define battleship_game_AiClientService_hpp

#include "dto/MessageDto.hpp"

namespace battleship { namespace game { namespace service {

class AiClientService {
public:
  oatpp::Object<battleship::game::dto::MessageDto> getRandomShot() const;
  oatpp::Object<battleship::game::dto::MessageDto> getCenterShot() const;
  oatpp::Object<battleship::game::dto::MessageDto> getSweepShot() const;
};

}}}

#endif
