#ifndef battleship_game_CurrentPlayerDto_hpp
#define battleship_game_CurrentPlayerDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class CurrentPlayerDto : public oatpp::DTO {
  DTO_INIT(CurrentPlayerDto, DTO)

  DTO_FIELD(Int32, currentPlayer);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
