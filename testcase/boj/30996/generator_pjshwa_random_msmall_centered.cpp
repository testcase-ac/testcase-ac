#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = rnd.next(1, 100);
  int M = rnd.next(1, 30);
  int Q = rnd.next(1, 5000);

  cout << N << ' ' << M << ' ' << Q << '\n';

  long double mu = 0, sumA = 0;
  for (int i = 1; i <= N; ++i) {
    int x = rnd.next(1, 1000);
    cout << x;

    mu += x * i;
    sumA += x;

    if (i < N) cout << ' ';
    else cout << '\n';
  }
  mu /= sumA;

  for (int i = 1; i <= Q; ++i) {
    int p = rnd.next(1, 100);
    int r = (int)mu + rnd.next(-p, p);
    r = max(r, 1);
    r = min(r, N * M);
    cout << r << '\n';
  }
}
