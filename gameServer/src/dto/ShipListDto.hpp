#ifndef battleship_game_ShipListDto_hpp
#define battleship_game_ShipListDto_hpp

#include "ShipDto.hpp"

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class ShipListDto : public oatpp::DTO {
  DTO_INIT(ShipListDto, DTO)

  DTO_FIELD(Int32, player);
  DTO_FIELD(Vector<Object<ShipDto>>, ships);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
