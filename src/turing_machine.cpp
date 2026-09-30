#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

template <class A> class TuringMachine {
public:
  typedef enum { LEFT, RIGHT, STAY } Move;
  typedef std::function<size_t(void)> state_i_fun_t;
  typedef std::variant<int, state_i_fun_t> state_i_t;
  typedef std::map<A, std::tuple<A, Move, state_i_t>> Q;

  TuringMachine(const std::deque<A> &init, const std::vector<Q> &q)
      : tape(init), q(q), state(0),
        position(std::find_if(tape.begin(), tape.end(),
                              [](const A &a) { return a != A::LAMBDA; })) {}
  TuringMachine(const std::string &init, const std::vector<Q> &q)
      : tape(init.size()), q(q), state(0), position(tape.begin()) {
    for (int i = 0; i < init.size(); i++)
      tape[i] = (A)init[i];
    position = std::find_if(tape.begin(), tape.end(),
                            [](const A &a) { return a != A::LAMBDA; });
  }

  bool process_cell() {
    if (q[state].size() == 0)
      return false;
    if (q[state].count(*position) != 1)
      throw std::runtime_error(std::string("in state q") + std::to_string(state) + " symbol '" + (char)*position + "' is unhandled");
    auto &neostate = q[state][*position];
    *position = std::get<A>(neostate);
    auto state_var = std::get<state_i_t>(neostate);
    if (std::holds_alternative<int>(state_var))
      state = std::get<int>(state_var);
    else
      state = std::get<state_i_fun_t>(state_var)();
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
  friend std::ostream &operator<<(std::ostream &os,
                                  const TuringMachine<A> &tm) {
    if (tm.state >= 0 && tm.q[tm.state].size())
      os << 'q' << tm.state << ": ";
    else 
      os << 'P' << ": ";
    for (auto ii = tm.tape.begin(); ii != tm.tape.end(); ii++) {
      if (ii == tm.position)
        os << '[';
      else if (ii - 1 != tm.position)
        os << ' ';
      os << (char)*ii;
      if (ii == tm.position)
        os << ']';
    }
    os << std::endl;
    return os;
  }

  const size_t P() const {
    if (q.size() == 0)
      return -1;
    return q.size() - 1;
  }

private:
  std::vector<Q> q;
  int state;
  std::deque<A> tape;
  decltype(tape.begin()) position;
};
