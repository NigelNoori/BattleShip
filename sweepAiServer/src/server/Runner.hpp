#ifndef battleship_sweep_Runner_hpp
#define battleship_sweep_Runner_hpp

#include <list>
#include <thread>

namespace battleship { namespace sweepai {

class Runner {
public:
  Runner();
  void run(std::list<std::thread>& acceptingThreads);
};

}}

#endif
