#ifndef battleship_sweep_SweepAiController_hpp
#define battleship_sweep_SweepAiController_hpp

#include "server/Constants.hpp"
#include "dto/ShotDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace sweepai { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController)

class SweepAiController : public oatpp::web::server::api::ApiController {
public:
  SweepAiController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper, battleship::sweepai::Qualifiers::SERVICE_SWEEP))
    : oatpp::web::server::api::ApiController(objectMapper) {}

  ENDPOINT_INFO(getSweepShot) {
    info->summary = "Get a sweep-pattern AI shot";
    info->addResponse<Object<dto::ShotDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/sweep/shot", getSweepShot) {
    auto shot = dto::ShotDto::createShared();
    shot->row = 0;
    shot->col = 1;
    return createDtoResponse(Status::CODE_200, shot);
  }
};

#include OATPP_CODEGEN_END(ApiController)

}}}

#endif
