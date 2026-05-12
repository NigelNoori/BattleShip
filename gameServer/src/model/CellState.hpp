#ifndef CELLSTATE_HPP_INCLUDED
#define CELLSTATE_HPP_INCLUDED

namespace model {

enum class CellState {
  EMPTY,   // nothing there / not shot yet
  SHIP,    // part of a ship
  HIT,     // ship got hit
  MISS     // shot but missed
};

}  // namespace model

#endif  // CELLSTATE_HPP_INCLUDED
