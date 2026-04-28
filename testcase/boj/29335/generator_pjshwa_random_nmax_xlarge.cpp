#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 3e5;
  printf("%d\n", N);
  for (int i = 1; i <= N; i++) {
    int x = rnd.next(1, (int)1e9);
    int y = rnd.next(1, (int)1e9);
    printf("%d %d\n", x, y);
  }
}
