#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = rnd.next(1, 4000);
  vector<int> xs;
  for (int i = 1; i <= N; i++) {
    xs.push_back(rnd.next(0, (int)1e9));
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  N = xs.size();
  printf("%d\n", N);
  for (int i = 0; i < N; i++) {
    printf("%d%c", xs[i], " \n"[i == N - 1]);
  }
}
