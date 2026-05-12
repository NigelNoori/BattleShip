#ifndef battleship_game_PlaceShipDto_hpp
#define battleship_game_PlaceShipDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class PlaceShipDto : public oatpp::DTO {
  DTO_INIT(PlaceShipDto, DTO)

  DTO_FIELD(Int32, player);
  DTO_FIELD(String, shipName);
  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
  DTO_FIELD(String, orientation);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
