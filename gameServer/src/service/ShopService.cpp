#include "ShopService.hpp"
#include <string>

namespace battleship { namespace game { namespace service {

// ── catalog definition ───────────────────────────────────────────────────────
// Ships: Patrol(2,2pts) Submarine(3,3pts) Destroyer(3,4pts) Battleship(4,6pts) Carrier(5,8pts)

struct ShipDef { const char* name; int size; int cost; };
static const ShipDef CATALOG[] = {
  { "Patrol",     2, 2 },
  { "Submarine",  3, 3 },
  { "Destroyer",  3, 4 },
  { "Battleship", 4, 6 },
  { "Carrier",    5, 8 },
};
static const int BUDGET = 20;

// ── public API ───────────────────────────────────────────────────────────────

oatpp::Object<ShopCatalogDto> ShopService::getCatalog() const {
  auto result   = ShopCatalogDto::createShared();
  result->budget = BUDGET;
  result->catalog = oatpp::Vector<oatpp::Object<ShipTypeDto>>::createShared();

  for (const auto& def : CATALOG) {
    auto item   = ShipTypeDto::createShared();
    item->name  = def.name;
    item->size  = def.size;
    item->cost  = def.cost;
    result->catalog->push_back(item);
  }
  return result;
}

oatpp::Object<ShopBuyResponseDto> ShopService::buyFleet(
    const oatpp::Object<ShopBuyRequestDto>& body) const {

  auto result = ShopBuyResponseDto::createShared();
  result->startingBudget = BUDGET;
  result->fleet = oatpp::Vector<oatpp::Object<PurchasedShipDto>>::createShared();

  if (!body || !body->ships) {
    result->success = false;
    result->message = "Invalid request";
    result->spent = 0;
    result->remainingBudget = BUDGET;
    return result;
  }

  int spent = 0;

  // Tally cost first
  for (const auto& item : *body->ships) {
    if (!item || !item->name) continue;
    const std::string shipName = item->name->c_str();
    const int qty = item->quantity ? item->quantity.getValue(0) : 0;

    for (const auto& def : CATALOG) {
      if (shipName == def.name) {
        spent += def.cost * qty;
        break;
      }
    }
  }

  if (spent > BUDGET) {
    result->success         = false;
    result->message         = "Not enough budget";
    result->spent           = spent;
    result->remainingBudget = BUDGET - spent;
    return result;
  }

  if (spent == 0) {
    result->success         = false;
    result->message         = "No valid ships selected";
    result->spent           = 0;
    result->remainingBudget = BUDGET;
    return result;
  }

  // Build fleet list
  for (const auto& item : *body->ships) {
    if (!item || !item->name) continue;
    const std::string shipName = item->name->c_str();
    const int qty = item->quantity ? item->quantity.getValue(0) : 0;

    for (const auto& def : CATALOG) {
      if (shipName == def.name) {
        for (int i = 0; i < qty; i++) {
          auto ship  = PurchasedShipDto::createShared();
          ship->name = def.name;
          ship->size = def.size;
          result->fleet->push_back(ship);
        }
        break;
      }
    }
  }

  result->success         = true;
  result->message         = "Fleet purchased successfully";
  result->spent           = spent;
  result->remainingBudget = BUDGET - spent;
  result->rows            = body->rows ? body->rows.getValue(5) : 5;
  result->cols            = body->cols ? body->cols.getValue(5) : 5;
  return result;
}

}}}
