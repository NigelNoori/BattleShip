#ifndef battleship_game_SwaggerComponent_hpp
#define battleship_game_SwaggerComponent_hpp

#include "Constants.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp-swagger/Controller.hpp"

#include "oatpp/core/macro/component.hpp"

namespace battleship { namespace game {

class SwaggerComponent {
public:
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)(Qualifiers::SERVICE_GAME, [] {
    oatpp::swagger::DocumentInfo::Builder builder;
    builder
      .setTitle("Battleship Game Server")
      .setDescription("Main REST gateway for Battleship")
      .setVersion("1.0")
      .setContactName("Battleship Team")
      .setLicenseName("None");
    return builder.build();
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)(Qualifiers::SERVICE_GAME, [] {
    return oatpp::swagger::Resources::loadResources("/usr/local/include/oatpp-1.3.0/bin/oatpp-swagger/res");
  }());
};

}}

#endif
