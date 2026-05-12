#include "RadarService.hpp"
#include <algorithm>
#include <sstream>

namespace battleship { namespace game { namespace service {

void RadarService::reset() {
  m_p1Used = false;
  m_p2Used = false;
}

bool RadarService::hasCharge(int player) const {
  return player == 1 ? !m_p1Used : !m_p2Used;
}

void RadarService::useCharge(int player) {
  if (player == 1) m_p1Used = true;
  else             m_p2Used = true;
}

oatpp::Object<RadarResponseDto> RadarService::scan(
    int player,
    int centerRow,
    int centerCol,
    const std::vector<std::string>& opponentBoard) const {

  auto result       = RadarResponseDto::createShared();
  result->player    = player;
  result->centerRow = centerRow;
  result->centerCol = centerCol;

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
    if (r >= static_cast<int>(opponentBoard.size())) break;
    const std::string& row = opponentBoard[r];
    for (int c = startCol; c <= endCol; ++c) {
      const int idx = c * 2;
      if (idx < static_cast<int>(row.size()) && row[idx] == 'S') {
        detected = true;
        break;
      }
    }
  }

  result->detected = detected;
  result->message  = detected ? "Enemy ships detected!" : "Sector is clear";
  return result;
}

}}}
