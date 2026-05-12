#include "AppComponent.hpp"
#include "Runner.hpp"

void run() {
  battleship::sweepai::AppComponent components(
    {"localhost", 8803},
    {"sweepai.virtualhost", 0}
  );

  std::list<std::thread> acceptingThreads;

  battleship::sweepai::Runner runner;
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
