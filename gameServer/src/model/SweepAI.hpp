#ifndef SWEEPAI_HPP_INCLUDED
#define SWEEPAI_HPP_INCLUDED

#include <string>
#include "model/AIStrategy.hpp"

namespace model {

// goes row by row left to right
class SweepAI : public AIStrategy {
 public:
  Position chooseShot(Board* board) override;
  std::string getName() const override { return "Row Sweep"; }
};

}  // namespace model

#endif  // SWEEPAI_HPP_INCLUDED
