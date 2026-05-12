#ifndef battleship_random_Runner_hpp
#define battleship_random_Runner_hpp

#include <list>
#include <thread>

namespace battleship { namespace randomai {

class Runner {
public:
  Runner();
  void run(std::list<std::thread>& acceptingThreads);
};

}}

#endif
