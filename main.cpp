#include <turing_machine.cpp>

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
};



typedef ::TuringMachine<MyA>::Move Move;

#define S(on, ch_to, move, next_state)                                         \
  {                                                                            \
    (on), { (next_state), (ch_to), (move) }                                    \
  }

int main() {
#define P 5
  TuringMachine<MyA> tm("^111*111^",
                        {
                            // Q
                            {
                                // 0
                                S(ONE, LAMBDA, Move::RIGHT, 1), // of pairs
                                S(STAR, ONE, Move::STAY, P),
                            },
                            {
                                // 1
                                S(ONE, ONE, Move::RIGHT, 1),
                                S(STAR, STAR, Move::RIGHT, 1),
                                S(LAMBDA, LAMBDA, Move::LEFT, 2),
                            },
                            {
                                // 2
                                S(ONE, LAMBDA, Move::LEFT, 3),
                                S(STAR, ONE, Move::LEFT, 4),
                            },
                            {
                                // 3
                                S(ONE, ONE, Move::LEFT, 3),
                                S(STAR, STAR, Move::LEFT, 3),
                                S(LAMBDA, LAMBDA, Move::RIGHT, 0),
                            },
                            {
                                // 4
                                S(ONE, ONE, Move::LEFT, 4),
                                S(LAMBDA, ONE, Move::STAY, P),
                            },
                            {
                                // empty is P and it happen to be 7
                            },
                        });
  tm.run();
}
