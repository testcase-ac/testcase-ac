#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 2e5;
  int M = 2e5;
  printf("%d %d\n", N, M);

  // randomly choose the number N times
  for (int i = 0; i < N; i++) {
    int K = 10;
    printf("%d ", K);

    for (int j = 0; j < K; j++) {
      printf("%d%c", rnd.next(1, M), j == K - 1 ? '\n' : ' ');
    }
  }
}
