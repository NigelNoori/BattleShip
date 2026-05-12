#ifndef SHIPCATALOG_HPP_INCLUDED
#define SHIPCATALOG_HPP_INCLUDED

#include <string>
#include <vector>

namespace model {

/** One ship type in the shop: name, size (cells), cost (points) */
struct ShipType {
  std::string name;
  int size;
  int cost;
};

/** Catalog of purchasable ships and player budget */
class ShipCatalog {
 public:
  ShipCatalog();

  const std::vector<ShipType>& getTypes() const { return types_; }
  int getBudget() const { return budget_; }
  static const int DEFAULT_BUDGET = 20;

 private:
  std::vector<ShipType> types_;
  int budget_;
};

}  // namespace model

#endif  // SHIPCATALOG_HPP_INCLUDED
