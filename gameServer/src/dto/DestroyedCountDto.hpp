#ifndef battleship_game_DestroyedCountDto_hpp
#define battleship_game_DestroyedCountDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class DestroyedCountDto : public oatpp::DTO {
  DTO_INIT(DestroyedCountDto, DTO)

  DTO_FIELD(Int32, player);
  DTO_FIELD(Int32, destroyedCount);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
