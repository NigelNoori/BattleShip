#ifndef RANDOMAI_HPP_INCLUDED
#define RANDOMAI_HPP_INCLUDED

#include <string>
#include "model/AIStrategy.hpp"

namespace model {

class RandomAI : public AIStrategy {
 public:
  Position chooseShot(Board* board) override;
  std::string getName() const override { return "Random"; }
};

}  // namespace model

#endif  // RANDOMAI_HPP_INCLUDED
