#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 4000;
  printf("%d\n", N);
  for (int i = 0; i < N; i++) {
    printf("%d%c", i, " \n"[i == N - 1]);
  }
}
