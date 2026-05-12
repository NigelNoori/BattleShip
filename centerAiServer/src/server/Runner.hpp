#ifndef battleship_center_Runner_hpp
#define battleship_center_Runner_hpp

#include <list>
#include <thread>

namespace battleship { namespace centerai {

class Runner {
public:
  Runner();
  void run(std::list<std::thread>& acceptingThreads);
};

}}

#endif
