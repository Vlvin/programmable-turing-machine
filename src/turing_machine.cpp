#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

template <class A> class TuringMachine {
public:
  typedef enum { LEFT, RIGHT, STAY } Move;
  typedef std::map<A, std::tuple<size_t, A, Move>> Q;

  TuringMachine(const std::deque<A> &init, const std::vector<Q> &q)
      : tape(init), q(q), state(0),
        position(std::find_if(tape.begin(), tape.end(),
                              [](const A &a) { return a != A::LAMBDA; })) {}

  bool process_cell() {
    if (q[state].size() == 0)
      return false;
    auto &neostate = q[state][*position];
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

  void print_tape() {
    for (auto &a : tape) {
      std::cout << (char)a << ' ';
    }
    std::cout << std::endl;
  }
  void run() {
    std::cout << *this;
    while (this->process_cell())
      std::cout << *this;
  }
  friend std::ostream& operator<<(std::ostream& os, const TuringMachine<A> &tm) {
    for (auto ii = tm.tape.begin(); ii != tm.tape.end(); ii++) {
      if (ii == tm.position)
        os << '[';
      else if (ii-1 != tm.position)
        os << ' ';
      os << (char)*ii;
      if (ii == tm.position)
        os << ']';
    }
    os << std::endl;
    return os;
  }

private:
  std::vector<Q> q;
  size_t state;
  std::deque<A> tape;
  decltype(tape.begin()) position;
};
