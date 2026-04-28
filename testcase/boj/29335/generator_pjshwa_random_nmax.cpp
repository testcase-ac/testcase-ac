#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int method_X = atoi(argv[1]);
  int method_Y = atoi(argv[2]);

  int N = 3e5, MAX = 1e9;
  printf("%d\n", N);

  vector<int> xs, ys;
  for (int i = 1; i <= N; i++) {
    int x = rnd.next(1, MAX);
    int y = rnd.next(1, MAX);
    xs.push_back(x);
    ys.push_back(y);
  }

  if (method_X == 0) sort(xs.begin(), xs.end());
  else if (method_X == 1) sort(xs.begin(), xs.end(), greater<int>());
  else if (method_X == 2) shuffle(xs.begin(), xs.end());

  if (method_Y == 0) sort(ys.begin(), ys.end());
  else if (method_Y == 1) sort(ys.begin(), ys.end(), greater<int>());
  else if (method_Y == 2) shuffle(ys.begin(), ys.end());

  for (int i = 0; i < N; i++) {
    printf("%d %d\n", xs[i], ys[i]);
  }
}
