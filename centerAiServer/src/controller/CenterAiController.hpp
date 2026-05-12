#ifndef battleship_center_CenterAiController_hpp
#define battleship_center_CenterAiController_hpp

#include "server/Constants.hpp"
#include "dto/ShotDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace centerai { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController)

class CenterAiController : public oatpp::web::server::api::ApiController {
public:
  CenterAiController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper, battleship::centerai::Qualifiers::SERVICE_CENTER))
    : oatpp::web::server::api::ApiController(objectMapper) {}

  ENDPOINT_INFO(getCenterShot) {
    info->summary = "Get a center-priority AI shot";
    info->addResponse<Object<dto::ShotDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/center/shot", getCenterShot) {
    auto shot = dto::ShotDto::createShared();
    shot->row = 2;
    shot->col = 2;
    return createDtoResponse(Status::CODE_200, shot);
  }
};

#include OATPP_CODEGEN_END(ApiController)

}}}

#endif
