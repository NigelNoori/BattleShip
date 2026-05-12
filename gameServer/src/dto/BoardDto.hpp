#ifndef battleship_game_BoardDto_hpp
#define battleship_game_BoardDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BoardDto : public oatpp::DTO {
  DTO_INIT(BoardDto, DTO)

  DTO_FIELD(Vector<String>, rows);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
