#ifndef CENTERAI_HPP_INCLUDED
#define CENTERAI_HPP_INCLUDED

#include <string>
#include "model/AIStrategy.hpp"

namespace model {

// shoots center first then works outward
class CenterAI : public AIStrategy {
 public:
  Position chooseShot(Board* board) override;
  std::string getName() const override { return "Center Hunter"; }
};

}  // namespace model

#endif  // CENTERAI_HPP_INCLUDED
