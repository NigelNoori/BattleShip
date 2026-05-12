#ifndef battleship_random_RandomAiController_hpp
#define battleship_random_RandomAiController_hpp

#include "server/Constants.hpp"
#include "dto/ShotDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace battleship { namespace randomai { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController)

class RandomAiController : public oatpp::web::server::api::ApiController {
public:
  RandomAiController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper, battleship::randomai::Qualifiers::SERVICE_RANDOM))
    : oatpp::web::server::api::ApiController(objectMapper) {}

  ENDPOINT_INFO(getRandomShot) {
    info->summary = "Get a random AI shot";
    info->addResponse<Object<dto::ShotDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/random/shot", getRandomShot) {
    auto shot = dto::ShotDto::createShared();
    shot->row = 0;
    shot->col = 0;
    return createDtoResponse(Status::CODE_200, shot);
  }
};

#include OATPP_CODEGEN_END(ApiController)

}}}

#endif
