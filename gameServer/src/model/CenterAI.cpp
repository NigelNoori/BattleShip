#include "model/CenterAI.hpp"
#include <vector>

namespace model {

Position CenterAI::chooseShot(Board* board) {
  Position result;
  result.row = -1;
  result.col = -1;
  if (board == nullptr) return result;
  int rows = board->getRows();
  int cols = board->getCols();
  int centerRow = rows / 2;
  int centerCol = cols / 2;

  std::vector<Position> available;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!board->alreadyShot(i, j)) {
        Position p;
        p.row = i;
        p.col = j;
        available.push_back(p);
      }
    }
  }
  if (available.size() == 0) return result;

  Position best = available[0];
  int bestDist = (centerRow - best.row) * (centerRow - best.row) +
      (centerCol - best.col) * (centerCol - best.col);
  for (size_t i = 1; i < available.size(); i++) {
    int dist = (centerRow - available[i].row) * (centerRow - available[i].row) +
        (centerCol - available[i].col) * (centerCol - available[i].col);
    if (dist < bestDist) {
      bestDist = dist;
      best = available[i];
    }
  }
  return best;
}

}  // namespace model
