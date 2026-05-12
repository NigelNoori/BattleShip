#include "model/Board.hpp"

namespace model {

Board::Board(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  grid_.resize(rows);
  for (int i = 0; i < rows; i++) {
    grid_[i].resize(cols);
    for (int j = 0; j < cols; j++) {
      grid_[i][j] = CellState::EMPTY;
    }
  }
}

int Board::getRows() const {
  return rows_;
}

int Board::getCols() const {
  return cols_;
}

bool Board::inBounds(int row, int col) const {
  if (row < 0 || row >= rows_) return false;
  if (col < 0 || col >= cols_) return false;
  return true;
}

bool Board::canPlaceAt(int startRow, int startCol, int size,
                      bool horizontal) const {
  if (size <= 0) return false;
  for (int i = 0; i < size; i++) {
    int row;
    int col;
    if (horizontal) {
      row = startRow;
      col = startCol + i;
    } else {
      row = startRow + i;
      col = startCol;
    }
    if (!inBounds(row, col)) return false;
    if (grid_[row][col] == CellState::SHIP) return false;
  }
  return true;
}

CellState Board::getCellState(int row, int col) const {
  if (!inBounds(row, col)) return CellState::EMPTY;
  return grid_[row][col];
}

CellState Board::getOpponentView(int row, int col) const {
  if (!inBounds(row, col)) return CellState::EMPTY;
  CellState cellState = grid_[row][col];
  if (cellState == CellState::SHIP) {
    return CellState::EMPTY;
  }
  return cellState;
}

bool Board::placeShip(Ship* ship, int startRow, int startCol, bool horizontal) {
  if (ship == nullptr) return false;
  int size = ship->getSize();
  if (!canPlaceAt(startRow, startCol, size, horizontal)) return false;

  std::vector<Position> positions;
  for (int i = 0; i < size; i++) {
    int row;
    int col;
    if (horizontal) {
      row = startRow;
      col = startCol + i;
    } else {
      row = startRow + i;
      col = startCol;
    }
    grid_[row][col] = CellState::SHIP;
    Position p;
    p.row = row;
    p.col = col;
    positions.push_back(p);
  }
  ship->setPositions(positions);
  return true;
}

CellState Board::recordShot(int row, int col) {
  if (!inBounds(row, col)) return CellState::MISS;
  if (grid_[row][col] == CellState::HIT) return CellState::HIT;
  if (grid_[row][col] == CellState::MISS) return CellState::MISS;

  if (grid_[row][col] == CellState::SHIP) {
    Ship* hitShip = getShipAt(row, col);
    if (hitShip != nullptr) {
      Position pos;
      pos.row = row;
      pos.col = col;
      hitShip->takeHit(pos);
    }
    grid_[row][col] = CellState::HIT;
    return CellState::HIT;
  }

  grid_[row][col] = CellState::MISS;
  return CellState::MISS;
}

bool Board::alreadyShot(int row, int col) const {
  if (!inBounds(row, col)) return false;
  if (grid_[row][col] == CellState::HIT) return true;
  if (grid_[row][col] == CellState::MISS) return true;
  return false;
}

Ship* Board::getShipAt(int row, int col) const {
  for (size_t i = 0; i < ships_.size(); i++) {
    std::vector<Position> shipPositions = ships_[i]->getPositions();
    for (size_t j = 0; j < shipPositions.size(); j++) {
      if (shipPositions[j].row == row && shipPositions[j].col == col) {
        return ships_[i].get();
      }
    }
  }
  return nullptr;
}

const std::vector<std::shared_ptr<Ship>>& Board::getShips() const {
  return ships_;
}

void Board::addShip(std::shared_ptr<Ship> ship) {
  ships_.push_back(ship);
}

int Board::countSunkShips() const {
  int count = 0;
  for (size_t i = 0; i < ships_.size(); i++) {
    if (ships_[i]->isSunk()) {
      count++;
    }
  }
  return count;
}

Ship* Board::getShipToPlace() const {
  for (size_t i = 0; i < ships_.size(); i++) {
    if (ships_[i]->getPositions().empty()) {
      return ships_[i].get();
    }
  }
  return nullptr;
}
bool Board::radarScan(int centerRow, int centerCol) const {
  // Check a 3x3 area around the center
  for (int r = centerRow - 1; r <= centerRow + 1; r++) {
    for (int c = centerCol - 1; c <= centerCol + 1; c++) {
      if (inBounds(r, c) && grid_[r][c] == CellState::SHIP) {
        return true; // Found at least one piece of a ship
      }
    }
  }
  return false; // Sector is clear
}
}  // namespace model
