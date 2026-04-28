#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
 
  int N = atoi(argv[1]);
  printf("%d\n", N);

  // gets 2 numbers from argv
  int x1 = atoi(argv[2]), x2 = atoi(argv[3]);
  vector<int> R{x1, x2};

  // randomly choose the number N times
  for (int i = 0; i < N; i++) {
    int x = R[rnd.next(0, 1)];
    printf("%d", x);
    if (i != N - 1) printf(" ");
  }
  printf("\n");
}
