#ifndef battleship_random_AppComponent_hpp
#define battleship_random_AppComponent_hpp

#include "Constants.hpp"
#include "SwaggerComponent.hpp"

#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

namespace battleship { namespace randomai {

struct HostPort {
  oatpp::String host;
  v_uint16 port;
};

class AppComponent {
private:
  HostPort m_hostPort;
  HostPort m_virtualHost;

public:
  AppComponent(const HostPort& hostPort, const HostPort& virtualHost)
    : m_hostPort(hostPort), m_virtualHost(virtualHost) {}

  SwaggerComponent swaggerComponent;

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)(Qualifiers::SERVICE_RANDOM, [this] {
    return oatpp::network::virtual_::Interface::obtainShared(m_virtualHost.host);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)(Qualifiers::SERVICE_RANDOM, [this] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared({m_hostPort.host, m_hostPort.port});
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, virtualConnectionProvider)(Qualifiers::SERVICE_RANDOM_VH, [] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface, Qualifiers::SERVICE_RANDOM);
    return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)(Qualifiers::SERVICE_RANDOM, [] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)(Qualifiers::SERVICE_RANDOM, [] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());
};

}}

#endif
