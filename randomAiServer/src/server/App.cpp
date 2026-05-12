#include "AppComponent.hpp"
#include "Runner.hpp"

void run() {
  battleship::randomai::AppComponent components(
    {"localhost", 8801},
    {"randomai.virtualhost", 0}
  );

  std::list<std::thread> acceptingThreads;

  battleship::randomai::Runner runner;
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
