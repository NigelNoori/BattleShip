#ifndef DTOS_SHOPDTO_HPP
#define DTOS_SHOPDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ShipTypeDto : public oatpp::DTO {
DTO_INIT(ShipTypeDto, DTO)

DTO_FIELD(String, name);
DTO_FIELD(Int32, size);
DTO_FIELD(Int32, cost);
};

class ShopCatalogDto : public oatpp::DTO {
DTO_INIT(ShopCatalogDto, DTO)

DTO_FIELD(Int32, budget);
DTO_FIELD(Vector<Object<ShipTypeDto>>, catalog);
};

class PurchaseItemDto : public oatpp::DTO {
DTO_INIT(PurchaseItemDto, DTO)

DTO_FIELD(String, name);
DTO_FIELD(Int32, quantity);
};

class ShopBuyRequestDto : public oatpp::DTO {
DTO_INIT(ShopBuyRequestDto, DTO)

DTO_FIELD(Int32, rows);
DTO_FIELD(Int32, cols);
DTO_FIELD(Vector<Object<PurchaseItemDto>>, ships);
};

class PurchasedShipDto : public oatpp::DTO {
DTO_INIT(PurchasedShipDto, DTO)

DTO_FIELD(String, name);
DTO_FIELD(Int32, size);
};

class ShopBuyResponseDto : public oatpp::DTO {
DTO_INIT(ShopBuyResponseDto, DTO)

DTO_FIELD(Boolean, success);
DTO_FIELD(String, message);
DTO_FIELD(Int32, startingBudget);
DTO_FIELD(Int32, spent);
DTO_FIELD(Int32, remainingBudget);
DTO_FIELD(Int32, rows);
DTO_FIELD(Int32, cols);
DTO_FIELD(Vector<Object<PurchasedShipDto>>, fleet);
};

#include OATPP_CODEGEN_END(DTO)

#endif