#include "model/Ship.hpp"

namespace model {

Ship::Ship(const std::string& name, int size) {
  name_ = name;
  size_ = size;
  health_ = size;
}

std::string Ship::getName() const {
  return name_;
}

int Ship::getSize() const {
  return size_;
}

int Ship::getHealth() const {
  return health_;
}

bool Ship::isSunk() const {
  if (health_ <= 0) return true;
  return false;
}

const std::vector<Position>& Ship::getPositions() const {
  return positions_;
}

void Ship::setPositions(const std::vector<Position>& positions) {
  positions_ = positions;
}

bool Ship::takeHit(const Position& pos) {
  for (size_t i = 0; i < positions_.size(); i++) {
    if (positions_[i].row == pos.row && positions_[i].col == pos.col) {
      if (health_ > 0) {
        health_ = health_ - 1;
        return true;
      }
      return false;
    }
  }
  return false;
}

}  // namespace model
