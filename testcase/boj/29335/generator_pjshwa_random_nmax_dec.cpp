#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 3e5;
  printf("%d\n", N);

  vector<int> xs, ys;
  for (int i = 1; i <= N; i++) {
    int x = rnd.next(1, (int)1e9);
    int y = rnd.next(1, (int)1e9);
    xs.push_back(x);
    ys.push_back(y);
  }
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end(), greater<int>());

  for (int i = 0; i < N; i++) {
    printf("%d %d\n", xs[i], ys[i]);
  }
}
