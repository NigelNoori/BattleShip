#ifndef DTOS_ACHIEVEMENTDTO_HPP
#define DTOS_ACHIEVEMENTDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AchievementDto : public oatpp::DTO {
DTO_INIT(AchievementDto, DTO)

DTO_FIELD(Int32, player);
DTO_FIELD(Int32, rounds);
DTO_FIELD(Boolean, hotShot);
DTO_FIELD(Boolean, perfectVictory);
};

#include OATPP_CODEGEN_END(DTO)

#endif