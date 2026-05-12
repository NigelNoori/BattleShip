#ifndef battleship_center_ShotDto_hpp
#define battleship_center_ShotDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace centerai { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class ShotDto : public oatpp::DTO {
  DTO_INIT(ShotDto, DTO)

  DTO_FIELD(Int32, row);
  DTO_FIELD(Int32, col);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
