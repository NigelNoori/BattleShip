#ifndef battleship_game_Runner_hpp
#define battleship_game_Runner_hpp

#include <list>
#include <thread>

namespace battleship { namespace game {

class Runner {
public:
  Runner();
  void run(std::list<std::thread>& acceptingThreads);
};

}}

#endif
