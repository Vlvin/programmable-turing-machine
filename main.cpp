#include <deque>
#include <iostream>
#include <map>
#include <vector>

template <class A> class TuringMachine {
public:
  typedef enum {
    LEFT,
    RIGHT,
    STAY
  } Move;
  typedef std::map<A, std::pair<A, Move>> Q;
private:
  std::vector<Q> states;
  std::vector<A> values;
  std::deque<A> tape;
  decltype(tape.begin()) position;
};

int main() { 
  std::deque<int> deq = {0,1,2,3};
  auto i = deq.begin();
  deq.push_front(-1);
  std::cout << *i << std::endl;
}
