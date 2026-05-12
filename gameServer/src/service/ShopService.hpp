#ifndef battleship_game_ShopService_hpp
#define battleship_game_ShopService_hpp

#include "dto/ShopDto.hpp"

namespace battleship { namespace game { namespace service {

class ShopService {
public:
  // Returns the catalog with prices and the 20-point budget
  oatpp::Object<ShopCatalogDto> getCatalog() const;

  // Validates the purchase and returns fleet + spend summary
  oatpp::Object<ShopBuyResponseDto> buyFleet(
    const oatpp::Object<ShopBuyRequestDto>& body) const;
};

}}}

#endif
