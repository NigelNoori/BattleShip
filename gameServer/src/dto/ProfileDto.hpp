#ifndef DTOS_PROFILEDTO_HPP
#define DTOS_PROFILEDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ProfileDto : public oatpp::DTO {
  DTO_INIT(ProfileDto, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Int32, wins);
  DTO_FIELD(Int32, losses);
};

class CreateProfileRequestDto : public oatpp::DTO {
  DTO_INIT(CreateProfileRequestDto, DTO)

  DTO_FIELD(String, name);
};

class UpdateProfileRequestDto : public oatpp::DTO {
  DTO_INIT(UpdateProfileRequestDto, DTO)

  DTO_FIELD(Int32, wins);
  DTO_FIELD(Int32, losses);
};

class ProfileListDto : public oatpp::DTO {
  DTO_INIT(ProfileListDto, DTO)

  DTO_FIELD(Vector<Object<ProfileDto>>, profiles);
};

#include OATPP_CODEGEN_END(DTO)

#endif
