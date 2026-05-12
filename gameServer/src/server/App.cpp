#include "AppComponent.hpp"
#include "Runner.hpp"

void run() {
  battleship::game::AppComponent components(
    {"localhost", 8800},
    {"game.virtualhost", 0}
  );

  std::list<std::thread> acceptingThreads;

  battleship::game::Runner runner;
  runner.run(acceptingThreads);

  for (auto& thread : acceptingThreads) {
    thread.join();
  }
}

int main(int argc, const char * argv[]) {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
