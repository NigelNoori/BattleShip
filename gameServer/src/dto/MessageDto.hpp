#ifndef battleship_game_MessageDto_hpp
#define battleship_game_MessageDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace game { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO {
  DTO_INIT(MessageDto, DTO)

  DTO_FIELD(String, status);
  DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif
