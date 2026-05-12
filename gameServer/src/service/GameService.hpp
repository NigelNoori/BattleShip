#ifndef battleship_game_GameService_hpp
#define battleship_game_GameService_hpp

#include "dto/GameStateDto.hpp"
#include "dto/BoardDto.hpp"
#include "dto/ShipDto.hpp"
#include "dto/ShipListDto.hpp"
#include "dto/DestroyedCountDto.hpp"
#include "dto/CurrentPlayerDto.hpp"
#include "dto/StatsDto.hpp"
#include "dto/PlaceShipDto.hpp"
#include "dto/FireDto.hpp"
#include "dto/MessageDto.hpp"
#include "dto/WinnerDto.hpp"
#include "dto/AchievementDto.hpp"
#include "dto/RadarDto.hpp"

#include <string>
#include <utility>
#include <vector>

namespace battleship { namespace game { namespace service {

class GameService {
private:
  struct ShipRecord {
    std::string name;
    int size;
    int health;
    bool destroyed;
    int startRow;
    int startCol;
    std::string orientation;
    std::vector<std::pair<int, int>> cells;
  };

private:
  std::vector<std::string> m_player1Board;
  std::vector<std::string> m_player2Board;
  std::vector<ShipRecord> m_player1Ships;
  std::vector<ShipRecord> m_player2Ships;
  bool m_hasWinner;
  int m_winner;
  int m_currentPlayer;
  int m_shotsFired;

private:
  void resetBoards();
  bool isInsideBoard(int row, int col) const;
  void placeChar(std::vector<std::string>& board, int row, int col, char value);
  char getChar(const std::vector<std::string>& board, int row, int col) const;
  int getShipSize(const std::string& shipName) const;
  bool canPlaceShip(const std::vector<std::string>& board, int row, int col, int size, const std::string& orientation) const;
  std::vector<std::pair<int, int>> buildCells(int row, int col, int size, const std::string& orientation) const;
  ShipRecord* findShipAt(std::vector<ShipRecord>& ships, int row, int col);
  const ShipRecord* findShipAt(const std::vector<ShipRecord>& ships, int row, int col) const;
  int countDestroyed(const std::vector<ShipRecord>& ships) const;
  oatpp::Object<battleship::game::dto::ShipDto> toShipDto(const ShipRecord& ship) const;

public:
  GameService();

  oatpp::Object<battleship::game::dto::GameStateDto> getGameState() const;
  oatpp::Object<battleship::game::dto::MessageDto> placeShip(const oatpp::Object<battleship::game::dto::PlaceShipDto>& body);
  oatpp::Object<battleship::game::dto::MessageDto> fireShot(const oatpp::Object<battleship::game::dto::FireDto>& body);
  oatpp::Object<battleship::game::dto::WinnerDto> getWinner() const;

  oatpp::Object<battleship::game::dto::ShipListDto> getShipHealth(int player) const;
  oatpp::Object<battleship::game::dto::DestroyedCountDto> getDestroyedCount(int player) const;
  oatpp::Object<battleship::game::dto::CurrentPlayerDto> getCurrentPlayer() const;
  oatpp::Object<battleship::game::dto::StatsDto> getStats() const;
  oatpp::Object<battleship::game::dto::MessageDto> resetGame();
  oatpp::Object<battleship::game::dto::MessageDto> deleteShip(int player, int row, int col);

  // Radar: one charge per player, scans opponent 3x3 sector
  oatpp::Object<battleship::game::dto::RadarResponseDto> radarScan(int player, int centerRow, int centerCol);

  // Achievements: evaluate after a winner is found
  oatpp::Object<battleship::game::dto::AchievementDto> getAchievements(int winner) const;

  // Board access for external use (e.g. radar)
  const std::vector<std::string>& getBoard(int player) const;
  int getShipCount(int player) const;

private:
  bool m_p1RadarUsed = false;
  bool m_p2RadarUsed = false;
};

}}}

#endif
