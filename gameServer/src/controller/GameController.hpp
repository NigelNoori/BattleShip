/*#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <utility>
#include "model/AIStrategy.hpp"
#include "model/Game.hpp"
#include "view/IView.hpp"
#include "model/Profile.hpp"
#include "model/ShipCatalog.hpp"

namespace controller {

/** Controller - handles game flow, gets input from view, calls model */
/*class GameController {
 public:
  // DI: we inject the view and game so we can test with mocks
  GameController(view::IView* view, model::Game* game);
  GameController(view::IView* view, model::Game* game,
                 model::ProfileManager* profileManager);
  void run();

 private:
  view::IView* view_;
  model::Game* game_;
  model::ProfileManager* profileManager_;  // null = no profiles
  model::AIStrategy* p1AI_;  // null = P1 is human (used in AI vs AI mode)
  model::AIStrategy* p2AI_;  // null = P2 is human, else we own it
  int roundCount_;
  int p1Shots_;
  int p2Shots_;
  int p1Hits_;
  int p2Hits_;
  int p1Radars_;
  int p2Radars_;
  std::string p1ProfileName_;
  std::string p2ProfileName_;
  int gameRows_;
  int gameCols_;

  void runProfileMenu();
  std::vector<std::pair<std::string, int>> runShipShop(
      const std::string& playerLabel);
  void runPlacementPhase(model::Player player);
  void runBattlePhase();
  void displayOwnBoard(model::Board* board, const std::string& title);
  void displayOpponentBoard(model::Board* board, const std::string& title);
  model::Position parseCoordinates(const std::string& input);
  bool parsePlacement(const std::string& input, int* row, int* col,
                     bool* horizontal);
  void showEndGameStats(model::Player winner);
  void showAchievements(model::Player winner);
};

}  // namespace controller

#endif  // GAMECONTROLLER_HPP_INCLUDED*/
