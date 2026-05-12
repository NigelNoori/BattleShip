#ifndef battleship_game_FireDto_hpp
#define battleship_game_FireDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class FireDto : public oatpp::DTO {
  DTO_INIT(FireDto, DTO)

  DTO_FIELD(Int32, attacker);
  DTO_FIELD(Int32, defender);
  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
