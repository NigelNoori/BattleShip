#include "Runner.hpp"
#include "AppComponent.hpp"

#include "controller/SweepAiController.hpp"

#include "oatpp-swagger/Controller.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"

namespace battleship { namespace sweepai {

Runner::Runner() {
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_SWEEP);

  oatpp::web::server::api::Endpoints docEndpoints;

  docEndpoints.append(
    router->addController(std::make_shared<controller::SweepAiController>())->getEndpoints()
  );

  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, documentInfo, Qualifiers::SERVICE_SWEEP);
  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, resources, Qualifiers::SERVICE_SWEEP);

  router->addController(oatpp::swagger::Controller::createShared(docEndpoints, documentInfo, resources));
}

void Runner::run(std::list<std::thread>& acceptingThreads) {
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_SWEEP);

  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  acceptingThreads.push_back(std::thread([connectionHandler] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_SWEEP);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("sweep-ai-service", "server is listening on port '%s'", connectionProvider->getProperty("port").getData());
    server.run();
  }));

  acceptingThreads.push_back(std::thread([connectionHandler] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_SWEEP_VH);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("sweep-ai-service", "server is listening on virtual interface '%s'", connectionProvider->getProperty("host").getData());
    server.run();
  }));
}

}}
