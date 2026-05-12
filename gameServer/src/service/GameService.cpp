#include "GameService.hpp"
#include <algorithm>

namespace battleship { namespace game { namespace service {

GameService::GameService()
  : m_hasWinner(false), m_winner(0), m_currentPlayer(1), m_shotsFired(0) {
  resetBoards();
}

void GameService::resetBoards() {
  m_player1Board = {
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~"
  };

  m_player2Board = {
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~",
    "~ ~ ~ ~ ~"
  };

  m_player1Ships.clear();
  m_player2Ships.clear();
  m_hasWinner = false;
  m_winner = 0;
  m_currentPlayer = 1;
  m_shotsFired = 0;
  m_p1RadarUsed = false;
  m_p2RadarUsed = false;
}

bool GameService::isInsideBoard(int row, int col) const {
  return row >= 0 && row < 5 && col >= 0 && col < 5;
}

void GameService::placeChar(std::vector<std::string>& board, int row, int col, char value) {
  const int strIndex = col * 2;
  board[row][strIndex] = value;
}

char GameService::getChar(const std::vector<std::string>& board, int row, int col) const {
  const int strIndex = col * 2;
  return board[row][strIndex];
}

int GameService::getShipSize(const std::string& shipName) const {
  if (shipName == "Carrier") return 5;
  if (shipName == "Battleship") return 4;
  if (shipName == "Cruiser") return 3;
  if (shipName == "Submarine") return 3;
  if (shipName == "Destroyer") return 2;
  return 1;
}

bool GameService::canPlaceShip(const std::vector<std::string>& board,
                               int row,
                               int col,
                               int size,
                               const std::string& orientation) const {
  for (int i = 0; i < size; ++i) {
    const int r = (orientation == "V") ? row + i : row;
    const int c = (orientation == "H") ? col + i : col;

    if (!isInsideBoard(r, c)) {
      return false;
    }

    if (getChar(board, r, c) != '~') {
      return false;
    }
  }

  return true;
}

std::vector<std::pair<int, int>> GameService::buildCells(int row,
                                                         int col,
                                                         int size,
                                                         const std::string& orientation) const {
  std::vector<std::pair<int, int>> cells;

  for (int i = 0; i < size; ++i) {
    const int r = (orientation == "V") ? row + i : row;
    const int c = (orientation == "H") ? col + i : col;
    cells.push_back({r, c});
  }

  return cells;
}

GameService::ShipRecord* GameService::findShipAt(std::vector<ShipRecord>& ships, int row, int col) {
  for (auto& ship : ships) {
    for (const auto& cell : ship.cells) {
      if (cell.first == row && cell.second == col) {
        return &ship;
      }
    }
  }
  return nullptr;
}

const GameService::ShipRecord* GameService::findShipAt(const std::vector<ShipRecord>& ships, int row, int col) const {
  for (const auto& ship : ships) {
    for (const auto& cell : ship.cells) {
      if (cell.first == row && cell.second == col) {
        return &ship;
      }
    }
  }
  return nullptr;
}

int GameService::countDestroyed(const std::vector<ShipRecord>& ships) const {
  int count = 0;
  for (const auto& ship : ships) {
    if (ship.destroyed) {
      ++count;
    }
  }
  return count;
}

oatpp::Object<battleship::game::dto::ShipDto> GameService::toShipDto(const ShipRecord& ship) const {
  auto dto = battleship::game::dto::ShipDto::createShared();
  dto->name = ship.name.c_str();
  dto->size = ship.size;
  dto->health = ship.health;
  dto->destroyed = ship.destroyed;
  return dto;
}

oatpp::Object<battleship::game::dto::GameStateDto> GameService::getGameState() const {
  auto state = battleship::game::dto::GameStateDto::createShared();
  state->status = "ok";
  state->currentPlayer = m_currentPlayer;

  auto board1 = battleship::game::dto::BoardDto::createShared();
  auto board2 = battleship::game::dto::BoardDto::createShared();

  board1->rows = oatpp::Vector<oatpp::String>::createShared();
  board2->rows = oatpp::Vector<oatpp::String>::createShared();

  for (const auto& row : m_player1Board) {
    board1->rows->push_back(row.c_str());
  }

  for (const auto& row : m_player2Board) {
    board2->rows->push_back(row.c_str());
  }

  state->player1Board = board1;
  state->player2Board = board2;

  state->player1Ships = oatpp::Vector<oatpp::Object<battleship::game::dto::ShipDto>>::createShared();
  for (const auto& ship : m_player1Ships) {
    state->player1Ships->push_back(toShipDto(ship));
  }

  state->player2Ships = oatpp::Vector<oatpp::Object<battleship::game::dto::ShipDto>>::createShared();
  for (const auto& ship : m_player2Ships) {
    state->player2Ships->push_back(toShipDto(ship));
  }

  return state;
}

oatpp::Object<battleship::game::dto::MessageDto> GameService::placeShip(
  const oatpp::Object<battleship::game::dto::PlaceShipDto>& body) {

  auto response = battleship::game::dto::MessageDto::createShared();

  if (!body || !body->shipName || !body->orientation) {
    response->status = "error";
    response->message = "Invalid request body";
    return response;
  }

  const int player = body->player ? body->player.getValue(0) : 0;
  const int row = body->row ? body->row.getValue(0) : -1;
  const int col = body->col ? body->col.getValue(0) : -1;
  const std::string shipName = body->shipName ? std::string(body->shipName->c_str()) : "";
  const std::string orientation = body->orientation ? std::string(body->orientation->c_str()) : "";
  if ((player != 1 && player != 2) || !isInsideBoard(row, col)) {
    response->status = "error";
    response->message = "Invalid player or coordinates";
    return response;
  }

  if (orientation != "H" && orientation != "V") {
    response->status = "error";
    response->message = "Orientation must be H or V";
    return response;
  }

  const int size = getShipSize(shipName);

  auto& board = (player == 1) ? m_player1Board : m_player2Board;
  auto& ships = (player == 1) ? m_player1Ships : m_player2Ships;

  if (!canPlaceShip(board, row, col, size, orientation)) {
    response->status = "error";
    response->message = "Ship cannot be placed there";
    return response;
  }

  ShipRecord record;
  record.name = shipName;
  record.size = size;
  record.health = size;
  record.destroyed = false;
  record.startRow = row;
  record.startCol = col;
  record.orientation = orientation;
  record.cells = buildCells(row, col, size, orientation);

  for (const auto& cell : record.cells) {
    placeChar(board, cell.first, cell.second, 'S');
  }

  ships.push_back(record);

  response->status = "ok";
  response->message = "Ship placed successfully";
  return response;
}

oatpp::Object<battleship::game::dto::MessageDto> GameService::fireShot(
  const oatpp::Object<battleship::game::dto::FireDto>& body) {

  auto response = battleship::game::dto::MessageDto::createShared();

  if (!body) {
    response->status = "error";
    response->message = "Invalid request body";
    return response;
  }

  const int attacker = body->attacker ? body->attacker.getValue(0) : 0;
  const int defender = body->defender ? body->defender.getValue(0) : 0;
  const int row = body->row ? body->row.getValue(0) : -1;
  const int col = body->col ? body->col.getValue(0) : -1;

  if ((attacker != 1 && attacker != 2) || (defender != 1 && defender != 2) || attacker == defender || !isInsideBoard(row, col)) {
    response->status = "error";
    response->message = "Invalid fire request";
    return response;
  }

  auto& targetBoard = (defender == 1) ? m_player1Board : m_player2Board;
  auto& targetShips = (defender == 1) ? m_player1Ships : m_player2Ships;

  const char current = getChar(targetBoard, row, col);

  if (current == 'X' || current == 'O') {
    response->status = "error";
    response->message = "Cell already targeted";
    return response;
  }

  ++m_shotsFired;

  if (current == 'S') {
    placeChar(targetBoard, row, col, 'X');

    ShipRecord* ship = findShipAt(targetShips, row, col);
    if (ship != nullptr) {
      ship->health -= 1;
      if (ship->health <= 0) {
        ship->health = 0;
        ship->destroyed = true;
        response->status = "ok";
        response->message = ("Destroyed " + ship->name).c_str();
      } else {
        response->status = "ok";
        response->message = ("Hit " + ship->name).c_str();
      }
    } else {
      response->status = "ok";
      response->message = "Hit";
    }
  } else {
    placeChar(targetBoard, row, col, 'O');
    response->status = "ok";
    response->message = "Miss";
  }

  if (!targetShips.empty() && countDestroyed(targetShips) == static_cast<int>(targetShips.size())) {
    m_hasWinner = true;
    m_winner = attacker;
  }

  m_currentPlayer = defender;
  return response;
}

oatpp::Object<battleship::game::dto::WinnerDto> GameService::getWinner() const {
  auto winner = battleship::game::dto::WinnerDto::createShared();
  winner->hasWinner = m_hasWinner;
  winner->winner = m_winner;
  winner->message = m_hasWinner ? "Winner found" : "No winner yet";
  return winner;
}

oatpp::Object<battleship::game::dto::ShipListDto> GameService::getShipHealth(int player) const {
  auto result = battleship::game::dto::ShipListDto::createShared();
  result->player = player;
  result->ships = oatpp::Vector<oatpp::Object<battleship::game::dto::ShipDto>>::createShared();

  const auto& ships = (player == 1) ? m_player1Ships : m_player2Ships;
  for (const auto& ship : ships) {
    result->ships->push_back(toShipDto(ship));
  }

  return result;
}

oatpp::Object<battleship::game::dto::DestroyedCountDto> GameService::getDestroyedCount(int player) const {
  auto result = battleship::game::dto::DestroyedCountDto::createShared();
  result->player = player;

  if (player == 1) {
    result->destroyedCount = countDestroyed(m_player1Ships);
  } else {
    result->destroyedCount = countDestroyed(m_player2Ships);
  }

  return result;
}

oatpp::Object<battleship::game::dto::CurrentPlayerDto> GameService::getCurrentPlayer() const {
  auto result = battleship::game::dto::CurrentPlayerDto::createShared();
  result->currentPlayer = m_currentPlayer;
  return result;
}

oatpp::Object<battleship::game::dto::StatsDto> GameService::getStats() const {
  auto result = battleship::game::dto::StatsDto::createShared();
  result->shotsFired = m_shotsFired;
  result->player1ShipsPlaced = static_cast<v_int32>(m_player1Ships.size());
  result->player2ShipsPlaced = static_cast<v_int32>(m_player2Ships.size());
  result->player1ShipsDestroyed = countDestroyed(m_player1Ships);
  result->player2ShipsDestroyed = countDestroyed(m_player2Ships);
  return result;
}

oatpp::Object<battleship::game::dto::MessageDto> GameService::resetGame() {
  resetBoards();
  auto response = battleship::game::dto::MessageDto::createShared();
  response->status = "ok";
  response->message = "Game reset successfully";
  return response;
}

oatpp::Object<battleship::game::dto::MessageDto> GameService::deleteShip(int player, int row, int col) {
  auto response = battleship::game::dto::MessageDto::createShared();

  if ((player != 1 && player != 2) || !isInsideBoard(row, col)) {
    response->status = "error";
    response->message = "Invalid player or coordinates";
    return response;
  }

  auto& board = (player == 1) ? m_player1Board : m_player2Board;
  auto& ships = (player == 1) ? m_player1Ships : m_player2Ships;

  int shipIndex = -1;
  for (int i = 0; i < static_cast<int>(ships.size()); ++i) {
    for (const auto& cell : ships[i].cells) {
      if (cell.first == row && cell.second == col) {
        shipIndex = i;
      }
    }
  }

  if (shipIndex == -1) {
    response->status = "error";
    response->message = "No ship found at that location";
    return response;
  }

  for (const auto& cell : ships[shipIndex].cells) {
    placeChar(board, cell.first, cell.second, '~');
  }

  ships.erase(ships.begin() + shipIndex);

  response->status = "ok";
  response->message = "Ship deleted successfully";
  return response;
}

oatpp::Object<battleship::game::dto::RadarResponseDto> GameService::radarScan(
    int player, int centerRow, int centerCol) {

  auto result = battleship::game::dto::RadarResponseDto::createShared();
  result->player    = player;
  result->centerRow = centerRow;
  result->centerCol = centerCol;

  if (player != 1 && player != 2) {
    result->detected = false;
    result->message  = "Invalid player";
    return result;
  }

  bool& used = (player == 1) ? m_p1RadarUsed : m_p2RadarUsed;
  if (used) {
    result->detected = false;
    result->message  = "Radar charge already used";
    return result;
  }

  if (!isInsideBoard(centerRow, centerCol)) {
    result->detected = false;
    result->message  = "Coordinates out of range";
    return result;
  }

  // Scan opponent's board
  const auto& opponentBoard = (player == 1) ? m_player2Board : m_player1Board;

  const int startRow = std::max(0, centerRow - 1);
  const int endRow   = std::min(4, centerRow + 1);
  const int startCol = std::max(0, centerCol - 1);
  const int endCol   = std::min(4, centerCol + 1);

  result->startRow = startRow;
  result->endRow   = endRow;
  result->startCol = startCol;
  result->endCol   = endCol;

  bool detected = false;
  for (int r = startRow; r <= endRow && !detected; ++r) {
    for (int c = startCol; c <= endCol; ++c) {
      if (getChar(opponentBoard, r, c) == 'S') {
        detected = true;
        break;
      }
    }
  }

  used             = true;
  result->detected = detected;
  result->message  = detected ? "Enemy ships detected!" : "Sector is clear";
  return result;
}

oatpp::Object<battleship::game::dto::AchievementDto> GameService::getAchievements(int winner) const {
  auto result           = battleship::game::dto::AchievementDto::createShared();
  result->player        = winner;
  result->rounds        = m_shotsFired;
  result->hotShot       = (m_shotsFired < 20);

  const auto& enemyShips = (winner == 1) ? m_player2Ships : m_player1Ships;
  int total     = static_cast<int>(enemyShips.size());
  int destroyed = countDestroyed(enemyShips);
  result->perfectVictory = (total > 0 && destroyed >= total);

  return result;
}

const std::vector<std::string>& GameService::getBoard(int player) const {
  return (player == 1) ? m_player1Board : m_player2Board;
}

int GameService::getShipCount(int player) const {
  return static_cast<int>(
    (player == 1) ? m_player1Ships.size() : m_player2Ships.size()
  );
}

}}}

