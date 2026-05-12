#ifndef GAMEDTO_HPP
#define GAMEDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Represents a single X,Y coordinate on the board.
 */
class CoordinateDto : public oatpp::DTO {
  DTO_INIT(CoordinateDto, DTO)
  
  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
};

/**
 * Represents a ship's current status.
 */
class ShipDto : public oatpp::DTO {
  DTO_INIT(ShipDto, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Int32, size);
  DTO_FIELD(Int32, health);
  DTO_FIELD(Boolean, isSunk);
};

/**
 * Catches data from POST /game/place
 */
class PlaceShipDto : public oatpp::DTO {
  DTO_INIT(PlaceShipDto, DTO)

  DTO_FIELD(String, shipName);
  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
  DTO_FIELD(Boolean, horizontal);
};

/**
 * Catches data from POST /game/fire
 */
class FireDto : public oatpp::DTO {
  DTO_INIT(FireDto, DTO)

  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
};

/**
 * Represents a player's board, including the grid and ships.
 */
class BoardDto : public oatpp::DTO {
  DTO_INIT(BoardDto, DTO)

  DTO_FIELD(Int32, rows);
  DTO_FIELD(Int32, cols);
  
  // A 2D array of Strings to hold cell states ("EMPTY", "SHIP", "HIT", "MISS")
  DTO_FIELD(Vector<Vector<String>>, grid);
  
  // A list of the ships currently on this board
  DTO_FIELD(Vector<oatpp::Object<ShipDto>>, ships);
};

/**
 * Represents the complete, overarching game state. 
 * This is what GET /game/state will return.
 */
class GameStateDto : public oatpp::DTO {
  DTO_INIT(GameStateDto, DTO)

  // "PLAYER1_PLACING", "PLAYER2_PLACING", "PLAYING", "GAME_OVER"
  DTO_FIELD(String, phase);
  
  // "PLAYER1" or "PLAYER2"
  DTO_FIELD(String, currentTurn);
  
  // "NONE", "PLAYER1", or "PLAYER2"
  DTO_FIELD(String, winner);

  // The actual boards
  DTO_FIELD(oatpp::Object<BoardDto>, board1);
  DTO_FIELD(oatpp::Object<BoardDto>, board2);
};

#include OATPP_CODEGEN_END(DTO)

#endif // GAMEDTO_HPP