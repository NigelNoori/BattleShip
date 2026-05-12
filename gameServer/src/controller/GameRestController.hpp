#ifndef battleship_game_GameRestController_hpp
#define battleship_game_GameRestController_hpp

#include "server/Constants.hpp"

#include "dto/GameStateDto.hpp"
#include "dto/PlaceShipDto.hpp"
#include "dto/FireDto.hpp"
#include "dto/MessageDto.hpp"
#include "dto/WinnerDto.hpp"
#include "dto/ShipListDto.hpp"
#include "dto/DestroyedCountDto.hpp"
#include "dto/CurrentPlayerDto.hpp"
#include "dto/StatsDto.hpp"
#include "dto/ProfileDto.hpp"
#include "dto/ShopDto.hpp"
#include "dto/AchievementDto.hpp"
#include "dto/RadarDto.hpp"
#include "service/GameService.hpp"
#include "service/AiClientService.hpp"
#include "service/ProfileService.hpp"
#include "service/ShopService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include <memory>

namespace battleship { namespace game { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController)

class GameRestController : public oatpp::web::server::api::ApiController {
private:
  static std::shared_ptr<battleship::game::service::GameService> getGameService() {
    static std::shared_ptr<battleship::game::service::GameService> service =
      std::make_shared<battleship::game::service::GameService>();
    return service;
  }

  static std::shared_ptr<battleship::game::service::AiClientService> getAiService() {
    static std::shared_ptr<battleship::game::service::AiClientService> service =
      std::make_shared<battleship::game::service::AiClientService>();
    return service;
  }

  static std::shared_ptr<battleship::game::service::ProfileService> getProfileService() {
    static std::shared_ptr<battleship::game::service::ProfileService> service =
      std::make_shared<battleship::game::service::ProfileService>();
    return service;
  }

  static std::shared_ptr<battleship::game::service::ShopService> getShopService() {
    static std::shared_ptr<battleship::game::service::ShopService> service =
      std::make_shared<battleship::game::service::ShopService>();
    return service;
  }

public:
  GameRestController(
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                    objectMapper,
                    battleship::game::Qualifiers::SERVICE_GAME))
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

  ENDPOINT_INFO(getGameState) {
    info->summary = "Get current Battleship game state";
    info->addResponse<Object<dto::GameStateDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/state", getGameState) {
    return createDtoResponse(Status::CODE_200, getGameService()->getGameState());
  }

  ENDPOINT_INFO(placeShip) {
    info->summary = "Place a ship on the board";
    info->addConsumes<Object<dto::PlaceShipDto>>("application/json");
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_400, "application/json");
  }
  ENDPOINT("POST", "/game/place", placeShip,
           BODY_DTO(Object<dto::PlaceShipDto>, body)) {
    auto response = getGameService()->placeShip(body);
    if (response->status == "error") {
      return createDtoResponse(Status::CODE_400, response);
    }
    return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT_INFO(fireShot) {
    info->summary = "Fire a shot at the opposing board";
    info->addConsumes<Object<dto::FireDto>>("application/json");
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_400, "application/json");
  }
  ENDPOINT("POST", "/game/fire", fireShot,
           BODY_DTO(Object<dto::FireDto>, body)) {
    auto response = getGameService()->fireShot(body);
    if (response->status == "error") {
      return createDtoResponse(Status::CODE_400, response);
    }
    return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT_INFO(getWinner) {
    info->summary = "Get the winner if the game has ended";
    info->addResponse<Object<dto::WinnerDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/winner", getWinner) {
    return createDtoResponse(Status::CODE_200, getGameService()->getWinner());
  }

  ENDPOINT_INFO(getShipHealth) {
    info->summary = "Get all ship health values for a player";
    info->addResponse<Object<dto::ShipListDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/ships/{player}/health", getShipHealth,
           PATH(Int32, player)) {
    return createDtoResponse(Status::CODE_200, getGameService()->getShipHealth(player));
  }

  ENDPOINT_INFO(getDestroyedCount) {
    info->summary = "Get number of destroyed ships for a player";
    info->addResponse<Object<dto::DestroyedCountDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/ships/{player}/destroyed", getDestroyedCount,
           PATH(Int32, player)) {
    return createDtoResponse(Status::CODE_200, getGameService()->getDestroyedCount(player));
  }

  ENDPOINT_INFO(getCurrentPlayer) {
    info->summary = "Get current player turn";
    info->addResponse<Object<dto::CurrentPlayerDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/current-player", getCurrentPlayer) {
    return createDtoResponse(Status::CODE_200, getGameService()->getCurrentPlayer());
  }

  ENDPOINT_INFO(getStats) {
    info->summary = "Get basic game statistics";
    info->addResponse<Object<dto::StatsDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/stats", getStats) {
    return createDtoResponse(Status::CODE_200, getGameService()->getStats());
  }

  ENDPOINT_INFO(resetGame) {
    info->summary = "Reset the game";
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/game/reset", resetGame) {
    return createDtoResponse(Status::CODE_200, getGameService()->resetGame());
  }

  ENDPOINT_INFO(deleteShip) {
    info->summary = "Delete a ship by cell location";
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_400, "application/json");
  }
  ENDPOINT("DELETE", "/game/ship/{player}/{row}/{col}", deleteShip,
           PATH(Int32, player),
           PATH(Int32, row),
           PATH(Int32, col)) {
    auto response = getGameService()->deleteShip(player, row, col);
    if (response->status == "error") {
      return createDtoResponse(Status::CODE_400, response);
    }
    return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT_INFO(getRandomAiShot) {
    info->summary = "Get a random AI shot through the gateway";
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/random/shot", getRandomAiShot) {
    return createDtoResponse(Status::CODE_200, getAiService()->getRandomShot());
  }

  ENDPOINT_INFO(getCenterAiShot) {
    info->summary = "Get a center AI shot through the gateway";
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/center/shot", getCenterAiShot) {
    return createDtoResponse(Status::CODE_200, getAiService()->getCenterShot());
  }

  ENDPOINT_INFO(getSweepAiShot) {
    info->summary = "Get a sweep AI shot through the gateway";
    info->addResponse<Object<dto::MessageDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/ai/sweep/shot", getSweepAiShot) {
    return createDtoResponse(Status::CODE_200, getAiService()->getSweepShot());
  }

  // ── Radar ──────────────────────────────────────────────────────────────────

  ENDPOINT_INFO(radarScan) {
    info->summary = "Radar sweep: scan a 3x3 sector on the opponent's board (one charge per player)";
    info->addConsumes<Object<dto::RadarRequestDto>>("application/json");
    info->addResponse<Object<dto::RadarResponseDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/game/radar", radarScan,
           BODY_DTO(Object<dto::RadarRequestDto>, body)) {
    if (!body) {
      auto err = dto::MessageDto::createShared();
      err->status  = "error";
      err->message = "Invalid request body";
      return createDtoResponse(Status::CODE_400, err);
    }
    const int player    = body->player    ? body->player.getValue(0)    : 0;
    const int centerRow = body->centerRow ? body->centerRow.getValue(0) : -1;
    const int centerCol = body->centerCol ? body->centerCol.getValue(0) : -1;
    return createDtoResponse(
      Status::CODE_200,
      getGameService()->radarScan(player, centerRow, centerCol)
    );
  }

  // ── Achievements ───────────────────────────────────────────────────────────

  ENDPOINT_INFO(getAchievements) {
    info->summary = "Get achievements for the winning player";
    info->addResponse<Object<dto::AchievementDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/game/achievements/{winner}", getAchievements,
           PATH(Int32, winner)) {
    return createDtoResponse(
      Status::CODE_200,
      getGameService()->getAchievements(winner)
    );
  }

  // ── Profiles ───────────────────────────────────────────────────────────────

  ENDPOINT_INFO(getAllProfiles) {
    info->summary = "Get all player profiles";
    info->addResponse<Object<ProfileListDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/profiles", getAllProfiles) {
    return createDtoResponse(Status::CODE_200, getProfileService()->getAllProfiles());
  }

  ENDPOINT_INFO(getProfile) {
    info->summary = "Get a single player profile by name";
    info->addResponse<Object<ProfileDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/profiles/{name}", getProfile,
           PATH(String, name)) {
    auto profile = getProfileService()->getProfile(name->c_str());
    if (!profile) {
      auto err = dto::MessageDto::createShared();
      err->status  = "error";
      err->message = "Profile not found";
      return createDtoResponse(Status::CODE_404, err);
    }
    return createDtoResponse(Status::CODE_200, profile);
  }

  ENDPOINT_INFO(createProfile) {
    info->summary = "Create a new player profile";
    info->addConsumes<Object<CreateProfileRequestDto>>("application/json");
    info->addResponse<Object<ProfileDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/profiles", createProfile,
           BODY_DTO(Object<CreateProfileRequestDto>, body)) {
    if (!body || !body->name) {
      auto err = dto::MessageDto::createShared();
      err->status  = "error";
      err->message = "Name is required";
      return createDtoResponse(Status::CODE_400, err);
    }
    return createDtoResponse(
      Status::CODE_200,
      getProfileService()->createProfile(body->name->c_str())
    );
  }

  ENDPOINT_INFO(recordWin) {
    info->summary = "Record a win for a player";
    info->addResponse<Object<ProfileDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/profiles/{name}/win", recordWin,
           PATH(String, name)) {
    return createDtoResponse(
      Status::CODE_200,
      getProfileService()->recordWin(name->c_str())
    );
  }

  ENDPOINT_INFO(recordLoss) {
    info->summary = "Record a loss for a player";
    info->addResponse<Object<ProfileDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/profiles/{name}/loss", recordLoss,
           PATH(String, name)) {
    return createDtoResponse(
      Status::CODE_200,
      getProfileService()->recordLoss(name->c_str())
    );
  }

  // ── Shop ───────────────────────────────────────────────────────────────────

  ENDPOINT_INFO(getShopCatalog) {
    info->summary = "Get the ship shop catalog with prices and budget";
    info->addResponse<Object<ShopCatalogDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/shop/catalog", getShopCatalog) {
    return createDtoResponse(Status::CODE_200, getShopService()->getCatalog());
  }

  ENDPOINT_INFO(buyFleet) {
    info->summary = "Purchase a fleet using the 20-point budget";
    info->addConsumes<Object<ShopBuyRequestDto>>("application/json");
    info->addResponse<Object<ShopBuyResponseDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/shop/buy", buyFleet,
           BODY_DTO(Object<ShopBuyRequestDto>, body)) {
    auto result = getShopService()->buyFleet(body);
    auto code   = (result->success && result->success.getValue(false))
                    ? Status::CODE_200 : Status::CODE_400;
    return createDtoResponse(code, result);
  }
};

#include OATPP_CODEGEN_END(ApiController)

}}}

#endif
