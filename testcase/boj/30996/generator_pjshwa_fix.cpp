#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int chooseN() {
  int mode = rnd.next(0, 2);
  if (mode == 0) return rnd.next(1, 5);
  if (mode == 1) return rnd.next(6, 30);
  return rnd.next(31, 100);
}

int chooseMQ() {
  int mode = rnd.next(0, 2);
  if (mode == 0) return rnd.next(1, 30);
  if (mode == 1) return rnd.next(31, 500);
  return rnd.next(501, 5000);
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int N = chooseN();
  int M = chooseMQ();
  int Q = chooseMQ();

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
    int r = rnd.next(1, N * M);
    cout << r << '\n';
  }
}
