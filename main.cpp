#include <linux/stddef.h>
#include <turing_machine.cpp>

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
};

typedef ::TuringMachine<MyA>::Move Move;

#define Arr(on, ch_to, move, next_state)                                       \
  {                                                                            \
    (on), { (ch_to), (move), (next_state) }                                    \
  }
int main() {
#define P [&tm]() { return tm.P(); } // P counts automatically
  TuringMachine<MyA> tm("^111*111^",
                        {
                            {
                                // 0
                                Arr(ONE, LAMBDA, Move::RIGHT, 1), // of pairs
                                Arr(STAR, ONE, Move::STAY, P),
                            },
                            {
                                // 1
                                Arr(ONE, ONE, Move::RIGHT, 1),
                                Arr(STAR, STAR, Move::RIGHT, 1),
                                Arr(LAMBDA, LAMBDA, Move::LEFT, 2),
                            },
                            {
                                // 2
                                Arr(ONE, LAMBDA, Move::LEFT, 3),
                                Arr(STAR, ONE, Move::LEFT, 4),
                            },
                            {
                                // 3
                                Arr(ONE, ONE, Move::LEFT, 3),
                                Arr(STAR, STAR, Move::LEFT, 3),
                                Arr(LAMBDA, LAMBDA, Move::RIGHT, 0),
                            },
                            {
                                // 4
                                Arr(ONE, ONE, Move::LEFT, 4),
                                Arr(LAMBDA, ONE, Move::STAY, P),
                            },
                            {
                                // empty is P and it happen to be 5
                            },
                        });
 tm.run();
}
