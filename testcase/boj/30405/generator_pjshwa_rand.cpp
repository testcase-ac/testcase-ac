#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int magni = atoi(argv[1]);
  int N = rnd.next(1, magni);
  int M = rnd.next(1, magni);
  printf("%d %d\n", N, M);

  // randomly choose the number N times
  for (int i = 0; i < N; i++) {
    int K = rnd.next(2, 10);
    printf("%d ", K);

    for (int j = 0; j < K; j++) {
      printf("%d%c", rnd.next(1, M), j == K - 1 ? '\n' : ' ');
    }
  }
}
