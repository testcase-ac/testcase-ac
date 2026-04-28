#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int L = rnd.next(1, 1200);
  int dif = rnd.next(1, max(1, L / 5));
  int N = rnd.next(1, 2000);

  vector<int> xs;
  for (int i = 1; i <= N; i++) {
    int p = rnd.next(0, L);
    if (p + dif <= L) {
      xs.push_back(p);
      xs.push_back(p + dif);
    }
    else if (p - dif >= 0) {
      xs.push_back(p);
      xs.push_back(p - dif);
    }
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  N = xs.size();
  printf("%d\n", N);
  for (int i = 0; i < N; i++) {
    printf("%d%c", xs[i], " \n"[i == N - 1]);
  }
}
