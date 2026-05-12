#ifndef battleship_game_WinnerDto_hpp
#define battleship_game_WinnerDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class WinnerDto : public oatpp::DTO {
  DTO_INIT(WinnerDto, DTO)

  DTO_FIELD(Boolean, hasWinner);
  DTO_FIELD(Int32, winner);
  DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
