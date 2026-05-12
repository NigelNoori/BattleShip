#include "AiClientService.hpp"

#include <array>
#include <cstdio>
#include <string>

namespace battleship { namespace game { namespace service {

static std::string runCommand(const std::string& cmd) {
  std::array<char, 256> buffer{};
  std::string result;

  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) {
    return "";
  }

  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
    result += buffer.data();
  }

  pclose(pipe);
  return result;
}

oatpp::Object<battleship::game::dto::MessageDto> AiClientService::getRandomShot() const {
  auto response = battleship::game::dto::MessageDto::createShared();
  response->status = "ok";
  response->message = runCommand("curl -s http://localhost:8801/ai/random/shot");
  return response;
}

oatpp::Object<battleship::game::dto::MessageDto> AiClientService::getCenterShot() const {
  auto response = battleship::game::dto::MessageDto::createShared();
  response->status = "ok";
  response->message = runCommand("curl -s http://localhost:8802/ai/center/shot");
  return response;
}

oatpp::Object<battleship::game::dto::MessageDto> AiClientService::getSweepShot() const {
  auto response = battleship::game::dto::MessageDto::createShared();
  response->status = "ok";
  response->message = runCommand("curl -s http://localhost:8803/ai/sweep/shot");
  return response;
}

}}}
