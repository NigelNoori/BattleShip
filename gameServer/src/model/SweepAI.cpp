#include "model/SweepAI.hpp"

namespace model {

Position SweepAI::chooseShot(Board* board) {
  Position result;
  result.row = -1;
  result.col = -1;
  if (board == nullptr) return result;
  int rows = board->getRows();
  int cols = board->getCols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!board->alreadyShot(i, j)) {
        result.row = i;
        result.col = j;
        return result;
      }
    }
  }
  return result;
}

}  // namespace model
