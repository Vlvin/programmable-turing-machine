#include <linux/stddef.h>
#include <turing_machine.cpp>

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
  A = 'a',
  EQ = '=',
};

#define Arr(on, ch_to, move, next_state)                                       \
  {                                                                            \
    (on), { (ch_to), (::TuringMachine<MyA>::Move::move), (next_state) }        \
  }
int main() {
#define P [&]() { return tm.P(); } // P counts automatically
  TuringMachine<MyA> tm("^1111111111111111*111111^",
                        {
                            {
                                // 0
                                Arr(ONE, LAMBDA, RIGHT, 1), // of pairs
                            },
                            {
                                // 1
                                Arr(ONE, ONE, RIGHT, 1),
                                Arr(STAR, STAR, RIGHT, 1),
                                Arr(LAMBDA, LAMBDA, LEFT, 9),
                            },
                            {
                                // 2
                                Arr(ONE, ONE, LEFT, 2),
                                Arr(STAR, STAR, LEFT, 2),
                                Arr(LAMBDA, LAMBDA, RIGHT, 3),
                            },
                            {
                                // 3
                                Arr(ONE, LAMBDA, RIGHT, 4),
                                Arr(STAR, LAMBDA, RIGHT, 8),
                            },
                            {
                                // 4
                                Arr(ONE, ONE, RIGHT, 4),
                                Arr(STAR, STAR, RIGHT, 4),
                                Arr(EQ, EQ, LEFT, 5),
                                Arr(A, A, LEFT, 5),
                            },
                            {
                                // 5
                                Arr(ONE, A, LEFT, 2),
                                Arr(STAR, STAR, RIGHT, 6),
                            },
                            {
                                // 6
                                Arr(ONE, ONE, RIGHT, 6),
                                Arr(EQ, EQ, RIGHT, 6),
                                Arr(A, ONE, RIGHT, 6),
                                Arr(LAMBDA, ONE, LEFT, 7),
                            },
                            {
                                // 7
                                Arr(ONE, ONE, LEFT, 7),
                                Arr(EQ, EQ, LEFT, 7),
                                Arr(STAR, STAR, LEFT, 7),
                                Arr(LAMBDA, ONE, STAY, 2),
                            },
                            {
                                // 8
                                Arr(ONE, LAMBDA, RIGHT, 8),
                                Arr(STAR, LAMBDA, RIGHT, 8),
                                Arr(A, LAMBDA, RIGHT, 8),
                                Arr(EQ, ONE, STAY, P),
                            },
                            {
                                // 9
                                Arr(ONE, EQ, LEFT, 2),
                            },
                            {
                                // empty is P and it happen to be 5
                            },
                        });
  tm.run();
}
