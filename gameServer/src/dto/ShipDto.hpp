#ifndef battleship_game_ShipDto_hpp
#define battleship_game_ShipDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class ShipDto : public oatpp::DTO {
  DTO_INIT(ShipDto, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Int32, size);
  DTO_FIELD(Int32, health);
  DTO_FIELD(Boolean, destroyed);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
