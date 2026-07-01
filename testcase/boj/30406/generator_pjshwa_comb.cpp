#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int chooseEvenN() {
  int mode = rnd.next(0, 2);
  if (mode == 0) return 2 * rnd.next(1, 15);
  if (mode == 1) return 2 * rnd.next(16, 500);
  return 2 * rnd.next(501, 100000);
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
 
  int N = chooseEvenN();
  printf("%d\n", N);

  int x1 = rnd.next(0, 3);
  int x2 = rnd.next(0, 3);
  while (x2 == x1) x2 = rnd.next(0, 3);
  vector<int> R{x1, x2};

  for (int i = 0; i < N; i++) {
    int x = R[rnd.next(0, 1)];
    printf("%d", x);
    if (i != N - 1) printf(" ");
  }
  printf("\n");
}
