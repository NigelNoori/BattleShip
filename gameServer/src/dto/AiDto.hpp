#ifndef DTOS_AIDTO_HPP
#define DTOS_AIDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AiShotDto : public oatpp::DTO {
  DTO_INIT(AiShotDto, DTO)

  DTO_FIELD(String, strategy);
  DTO_FIELD(Int32, player);
  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
  DTO_FIELD(String, coordinate);
};

#include OATPP_CODEGEN_END(DTO)

#endif
