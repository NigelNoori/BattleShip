#ifndef SHIP_HPP_INCLUDED
#define SHIP_HPP_INCLUDED

#include <string>
#include <vector>

namespace model {

// position on the board (0-based)
struct Position {
  int row;
  int col;

  bool operator==(const Position& other) const {
    return row == other.row && col == other.col;
  }
};

/** Ship - has a name, size, and tracks which cells it's on and its health */
class Ship {
 public:
  Ship(const std::string& name, int size);

  std::string getName() const;
  int getSize() const;
  int getHealth() const;
  bool isSunk() const;
  const std::vector<Position>& getPositions() const;
  void setPositions(const std::vector<Position>& positions);

  // returns true if this ship was hit at pos
  bool takeHit(const Position& pos);

 private:
  std::string name_;
  int size_;
  int health_;
  std::vector<Position> positions_;
};

}  // namespace model

#endif  // SHIP_HPP_INCLUDED
