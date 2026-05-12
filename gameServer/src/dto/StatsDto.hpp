#ifndef battleship_game_StatsDto_hpp
#define battleship_game_StatsDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class StatsDto : public oatpp::DTO {
  DTO_INIT(StatsDto, DTO)

  DTO_FIELD(Int32, shotsFired);
  DTO_FIELD(Int32, player1ShipsPlaced);
  DTO_FIELD(Int32, player2ShipsPlaced);
  DTO_FIELD(Int32, player1ShipsDestroyed);
  DTO_FIELD(Int32, player2ShipsDestroyed);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
