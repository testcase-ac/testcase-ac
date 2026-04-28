#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = 3e5, MAX = 1e9;
  printf("%d\n", N);

  vector<int> xs, ys;
  for (int i = 1; i <= N / 2; i++) {
    int x = rnd.next(2, MAX / 2);
    int y = rnd.next(MAX / 2 + 1, MAX - N / 2);
    xs.push_back(x);
    ys.push_back(y);
  }
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end(), greater<int>());

  for (int i = 0; i < N / 2; i++) {
    printf("%d %d\n", xs[i], ys[i]);
  }
  for (int i = 0; i < N / 2; i++) printf("1 %d\n", MAX - N / 2 + i + 1);
}
