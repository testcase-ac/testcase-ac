#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = rnd.next(1, 5);
  printf("%d\n", N);
  for (int i = 1; i <= N; i++) {
    int x = rnd.next(1, 10);
    int y = rnd.next(1, 10);
    printf("%d %d\n", x, y);
  }
}
