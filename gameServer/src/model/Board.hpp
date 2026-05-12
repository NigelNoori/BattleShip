#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <memory>
#include <vector>
#include "model/CellState.hpp"
#include "model/Ship.hpp"

namespace model {

/** Board - the grid, ships on it, and shot tracking */
class Board {
 public:
  Board(int rows, int cols);

  int getRows() const;
  int getCols() const;

  // owner sees their ships, opponent view hides them
  CellState getCellState(int row, int col) const;
  CellState getOpponentView(int row, int col) const;

  bool placeShip(Ship* ship, int startRow, int startCol, bool horizontal);
  CellState recordShot(int row, int col);
  bool alreadyShot(int row, int col) const;
  Ship* getShipAt(int row, int col) const;

  const std::vector<std::shared_ptr<Ship>>& getShips() const;
  void addShip(std::shared_ptr<Ship> ship);
  int countSunkShips() const;

  // next ship that hasn't been placed yet (positions empty)
  Ship* getShipToPlace() const;

  // NEW: Feature #4 - Radar Sweep
  bool radarScan(int centerRow, int centerCol) const;

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<CellState>> grid_;
  std::vector<std::shared_ptr<Ship>> ships_;

  bool inBounds(int row, int col) const;
  bool canPlaceAt(int startRow, int startCol, int size, bool horizontal) const;
};

}  // namespace model

#endif  // BOARD_HPP_INCLUDED
