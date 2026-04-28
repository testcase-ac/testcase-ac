#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
 
  int N = rnd.next(2, 200'000);
  if (N % 2 == 1) N--;
  printf("%d\n", N);

  // randomly choose the number N times
  for (int i = 0; i < N; i++) {
    int x = rnd.next(0, 3);
    printf("%d", x);
    if (i != N - 1) printf(" ");
  }
  printf("\n");
}
