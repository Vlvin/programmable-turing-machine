#include <deque>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

template <class A> class TuringMachine {
public:
  typedef enum { LEFT, RIGHT, STAY } Move;
  typedef std::map<A, std::tuple<size_t, A, Move>> Q;

  bool process_cell() {
    if (states[state].size() == 0)
      return false;
    auto &neostate = states[state][*position];
    *position = std::get<A>(neostate);
    state = std::get<size_t>(neostate);
    switch (std::get<Move>(neostate)) {
    case LEFT:
      if (position == tape.begin())
        tape.push_front(A::LAMBDA);
      position--;
      break;
    case RIGHT:
      if (position + 1 == tape.end())
        tape.push_back(A::LAMBDA);
      position++;
      break;
    case STAY:
      break;
    }
    return true;
  }

private:
  std::vector<Q> states;
  size_t state;
  std::vector<A> values;
  std::deque<A> tape;
  decltype(tape.begin()) position;
};

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
};

int main() {
  TuringMachine<MyA> tm;
  tm.process_cell();
}
