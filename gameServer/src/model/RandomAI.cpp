#include "model/RandomAI.hpp"
#include <random>
#include <vector>

namespace model {

Position RandomAI::chooseShot(Board* board) {
  Position result;
  result.row = -1;
  result.col = -1;
  if (board == nullptr) return result;
  int rows = board->getRows();
  int cols = board->getCols();
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
  static std::mt19937 rng(std::random_device {}());
std::uniform_int_distribution<int> dist(
    0, static_cast<int>(available.size()) - 1);
return available[dist(rng)];
}

}  // namespace model
