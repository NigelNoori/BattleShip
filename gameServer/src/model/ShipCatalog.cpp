#include "model/ShipCatalog.hpp"

namespace model {

ShipCatalog::ShipCatalog() : budget_(DEFAULT_BUDGET) {
  types_.push_back({"Patrol", 2, 2});
  types_.push_back({"Submarine", 3, 3});
  types_.push_back({"Destroyer", 3, 3});
  types_.push_back({"Battleship", 4, 4});
  types_.push_back({"Carrier", 5, 5});
}

}  // namespace model
