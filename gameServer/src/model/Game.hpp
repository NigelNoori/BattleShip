#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <vector>
#include <memory>
#include <utility>
#include <string>
#include "model/Board.hpp"
#include "model/Ship.hpp"

namespace model {

enum class GamePhase {
  PLAYER1_PLACING,
  PLAYER2_PLACING,
  PLAYING,
  GAME_OVER
};

enum class Player { PLAYER1, PLAYER2 };

/** Game - holds both boards, whose turn, phase, winner */
class Game {
 public:
  Game();
  Game(int rows, int cols);

  Board* getBoard1();
  Board* getBoard2();
  Board* getCurrentPlayerBoard();  // board we're defending
  Board* getOpponentBoard();       // board we're shooting at

  GamePhase getPhase() const;
  void setPhase(GamePhase phase);
  Player getCurrentTurn() const;
  void setCurrentTurn(Player p);
  void switchTurn();
  Player getWinner() const;
  void setWinner(Player p);

  int getRows() const;
  int getCols() const;
  std::vector<int> getShipSizes() const;
  bool allShipsPlaced() const;

  void reset();
  void reset(int rows, int cols);
  /** Reset with custom fleets (e.g. from ship-buying).
  Same fleet for both if fleet2 empty. */
  void reset(int rows, int cols,
             const std::vector<std::pair<std::string, int>>& fleet1,
             const std::vector<std::pair<std::string, int>>& fleet2);

 private:
  void initBoardsFromFleets(
      const std::vector<std::pair<std::string, int>>& f1,
      const std::vector<std::pair<std::string, int>>& f2);

  std::unique_ptr<Board> board1_;
  std::unique_ptr<Board> board2_;
  GamePhase phase_;
  Player currentTurn_;
  Player winner_;
  int rows_;
  int cols_;
  std::vector<int> shipSizes_;
  std::vector<std::string> shipNames_;
};

}  // namespace model

#endif  // GAME_HPP_INCLUDED
