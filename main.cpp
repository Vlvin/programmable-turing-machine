#include <algorithm>
#include <deque>
#include <initializer_list>
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

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
};

typedef ::TuringMachine<MyA>::Move Move;

int main() {
#define P 7
  TuringMachine<MyA> tm({ONE, ONE, ONE, ONE, ONE, ONE, STAR, ONE, ONE, ONE},
                        {
                            // vector
                            { // 0
                                // of maps
                                {ONE, {1, LAMBDA, Move::RIGHT}}, // of pairs
                                {STAR, {4, LAMBDA, Move::RIGHT}},
                            },
                            { // 1
                                {ONE, {1, ONE, Move::RIGHT}},
                                {STAR, {1, STAR, Move::RIGHT}},
                                {LAMBDA, {2, LAMBDA, Move::LEFT}},
                            },
                            { // 2
                                {ONE, {3, LAMBDA, Move::LEFT}},
                                {STAR, {6, ONE, Move::RIGHT}}, // difference 5->6
                            },
                            { // 3
                                {ONE, {3, ONE, Move::LEFT}},
                                {STAR, {3, STAR, Move::LEFT}},
                                {LAMBDA, {0, LAMBDA, Move::RIGHT}},
                            },
                            { // 4
                                {ONE, {4, LAMBDA, Move::RIGHT}},
                                {LAMBDA, {P, ONE, Move::STAY}},
                            },
                            { // 5
                                {LAMBDA, {P, LAMBDA, Move::RIGHT}},
                                {ONE, {5, ONE, Move::LEFT}},
                            },
                            { // 6
                              {LAMBDA, {5, ONE, Move::LEFT}} 
                            },
                            { // empty is P
                            },
                        });
  tm.run();
}
