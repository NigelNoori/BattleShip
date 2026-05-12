#ifndef AISTRATEGY_HPP_INCLUDED
#define AISTRATEGY_HPP_INCLUDED

#include <string>
#include "model/Board.hpp"
#include "model/Ship.hpp"

namespace model {

// base class for the different AI strategies
class AIStrategy {
 public:
  virtual ~AIStrategy() = default;
  virtual Position chooseShot(Board* board) = 0;
  virtual std::string getName() const = 0;
};

}  // namespace model

#endif  // AISTRATEGY_HPP_INCLUDED
