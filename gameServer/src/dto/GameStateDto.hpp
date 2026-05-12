#ifndef battleship_game_GameStateDto_hpp
#define battleship_game_GameStateDto_hpp

#include "BoardDto.hpp"
#include "ShipDto.hpp"

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class GameStateDto : public oatpp::DTO {
  DTO_INIT(GameStateDto, DTO)

  DTO_FIELD(String, status);
  DTO_FIELD(Int32, currentPlayer);
  DTO_FIELD(Object<BoardDto>, player1Board);
  DTO_FIELD(Object<BoardDto>, player2Board);
  DTO_FIELD(Vector<Object<ShipDto>>, player1Ships);
  DTO_FIELD(Vector<Object<ShipDto>>, player2Ships);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
