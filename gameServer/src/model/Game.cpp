#include "model/Game.hpp"

namespace model {

Game::Game() : Game(8, 8) {}

Game::Game(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  phase_ = GamePhase::PLAYER1_PLACING;
  currentTurn_ = Player::PLAYER1;
  winner_ = Player::PLAYER1;
  shipSizes_ = {2, 3, 3, 4, 5};
  shipNames_ = {"Patrol", "Submarine", "Destroyer", "Battleship", "Carrier"};
  std::vector<std::pair<std::string, int>> defaultFleet = {
      {"Patrol", 2}, {"Submarine", 3}, {"Destroyer", 3},
      {"Battleship", 4}, {"Carrier", 5}};
  initBoardsFromFleets(defaultFleet, defaultFleet);
}

Board* Game::getBoard1() {
  return board1_.get();
}

Board* Game::getBoard2() {
  return board2_.get();
}

Board* Game::getCurrentPlayerBoard() {
  if (phase_ == GamePhase::PLAYER1_PLACING) return board1_.get();
  if (phase_ == GamePhase::PLAYER2_PLACING) return board2_.get();
  if (currentTurn_ == Player::PLAYER1) return board1_.get();
  return board2_.get();
}

Board* Game::getOpponentBoard() {
  if (phase_ == GamePhase::PLAYER1_PLACING) return board2_.get();
  if (phase_ == GamePhase::PLAYER2_PLACING) return board1_.get();
  if (currentTurn_ == Player::PLAYER1) return board2_.get();
  return board1_.get();
}

GamePhase Game::getPhase() const {
  return phase_;
}

void Game::setPhase(GamePhase phase) {
  phase_ = phase;
}

Player Game::getCurrentTurn() const {
  return currentTurn_;
}

void Game::setCurrentTurn(Player p) {
  currentTurn_ = p;
}

void Game::switchTurn() {
  if (currentTurn_ == Player::PLAYER1) {
    currentTurn_ = Player::PLAYER2;
  } else {
    currentTurn_ = Player::PLAYER1;
  }
}

Player Game::getWinner() const {
  return winner_;
}

void Game::setWinner(Player p) {
  winner_ = p;
}

int Game::getRows() const {
  return rows_;
}

int Game::getCols() const {
  return cols_;
}

std::vector<int> Game::getShipSizes() const {
  return shipSizes_;
}

bool Game::allShipsPlaced() const {
  Board* board;
  if (phase_ == GamePhase::PLAYER1_PLACING) {
    board = board1_.get();
  } else {
    board = board2_.get();
  }
  int placed = 0;
  std::vector<std::shared_ptr<Ship>> ships = board->getShips();
  for (size_t i = 0; i < ships.size(); i++) {
    if (!ships[i]->getPositions().empty()) {
      placed++;
    }
  }
  return placed == static_cast<int>(shipSizes_.size());
}

void Game::reset() {
  reset(rows_, cols_);
}

void Game::reset(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  shipSizes_.clear();
  shipNames_.clear();
  shipSizes_ = {2, 3, 3, 4, 5};
  shipNames_ = {"Patrol", "Submarine", "Destroyer", "Battleship", "Carrier"};
  initBoardsFromFleets(
      std::vector<std::pair<std::string, int>>({
          {"Patrol", 2}, {"Submarine", 3}, {"Destroyer", 3},
          {"Battleship", 4}, {"Carrier", 5}}),
      std::vector<std::pair<std::string, int>>({
          {"Patrol", 2}, {"Submarine", 3}, {"Destroyer", 3},
          {"Battleship", 4}, {"Carrier", 5}}));
  phase_ = GamePhase::PLAYER1_PLACING;
  currentTurn_ = Player::PLAYER1;
  winner_ = Player::PLAYER1;
}

void Game::reset(int rows, int cols,
                 const std::vector<std::pair<std::string, int>>& fleet1,
                 const std::vector<std::pair<std::string, int>>& fleet2) {
  rows_ = rows;
  cols_ = cols;
  const std::vector<std::pair<std::string, int>>& f2 =
      fleet2.empty() ? fleet1 : fleet2;
  initBoardsFromFleets(fleet1, f2);
  shipSizes_.clear();
  shipNames_.clear();
  for (size_t i = 0; i < fleet1.size(); i++) {
    shipNames_.push_back(fleet1[i].first);
    shipSizes_.push_back(fleet1[i].second);
  }
  phase_ = GamePhase::PLAYER1_PLACING;
  currentTurn_ = Player::PLAYER1;
  winner_ = Player::PLAYER1;
}

void Game::initBoardsFromFleets(
    const std::vector<std::pair<std::string, int>>& f1,
    const std::vector<std::pair<std::string, int>>& f2) {
  board1_ = std::make_unique<Board>(rows_, cols_);
  board2_ = std::make_unique<Board>(rows_, cols_);
  for (size_t i = 0; i < f1.size(); i++) {
    std::shared_ptr<Ship> s1 =
        std::make_shared<Ship>(f1[i].first, f1[i].second);
    board1_->addShip(s1);
    }
  for (size_t i = 0; i < f2.size(); i++) {
    std::shared_ptr<Ship> s2 =
        std::make_shared<Ship>(f2[i].first, f2[i].second);
    board2_->addShip(s2);
  }
}

}  // namespace model
