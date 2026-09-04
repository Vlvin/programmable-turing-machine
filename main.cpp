#include <turing_machine.cpp>

enum MyA {
  LAMBDA = '^',
  ONE = '1',
  STAR = '*',
};

typedef ::TuringMachine<MyA>::Move Move;

int main() {
#define P 7
  TuringMachine<MyA> tm(
      {ONE, ONE, ONE, ONE, ONE, ONE, STAR, ONE, ONE, ONE},
      {
          // Q
          {
              // 0
              // of maps
              {ONE, {1, LAMBDA, Move::RIGHT}}, // of pairs
              {STAR, {4, LAMBDA, Move::RIGHT}},
          },
          {
              // 1
              {ONE, {1, ONE, Move::RIGHT}},
              {STAR, {1, STAR, Move::RIGHT}},
              {LAMBDA, {2, LAMBDA, Move::LEFT}},
          },
          {
              // 2
              {ONE, {3, LAMBDA, Move::LEFT}},
              {STAR, {6, ONE, Move::RIGHT}}, // difference 5->6
          },
          {
              // 3
              {ONE, {3, ONE, Move::LEFT}},
              {STAR, {3, STAR, Move::LEFT}},
              {LAMBDA, {0, LAMBDA, Move::RIGHT}},
          },
          {
              // 4
              {ONE, {4, LAMBDA, Move::RIGHT}},
              {LAMBDA, {P, ONE, Move::STAY}},
          },
          {
              // 5
              {LAMBDA, {P, LAMBDA, Move::RIGHT}},
              {ONE, {5, ONE, Move::LEFT}},
          },
          {// 6
           {LAMBDA, {5, ONE, Move::LEFT}}},
          {
              // empty is P and it happen to be 7
          },
      });
  tm.run();
}
