#ifndef DTOS_RADARDTO_HPP
#define DTOS_RADARDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class RadarRequestDto : public oatpp::DTO {
DTO_INIT(RadarRequestDto, DTO)

DTO_FIELD(Int32, player);
DTO_FIELD(Int32, centerRow);
DTO_FIELD(Int32, centerCol);
};

class RadarResponseDto : public oatpp::DTO {
DTO_INIT(RadarResponseDto, DTO)

DTO_FIELD(Boolean, detected);
DTO_FIELD(Int32, player);
DTO_FIELD(Int32, centerRow);
DTO_FIELD(Int32, centerCol);
DTO_FIELD(Int32, startRow);
DTO_FIELD(Int32, endRow);
DTO_FIELD(Int32, startCol);
DTO_FIELD(Int32, endCol);
DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif