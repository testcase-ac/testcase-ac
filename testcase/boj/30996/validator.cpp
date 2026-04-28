#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(1, 100, "N"); inf.readSpace();
  int M = inf.readInt(1, 5000, "M"); inf.readSpace();
  int Q = inf.readInt(1, 5000, "Q"); inf.readEoln();

  int sumA = 0;
  for (int i = 1; i <= N; ++i) {
    int x = inf.readInt(1, 1000, "A_i");
    sumA += x;

    if (i < N) inf.readSpace();
    else inf.readEoln();
  }

  for (int i = 1; i <= Q; ++i) {
    int x = inf.readInt(1, N * M, "x_i");
    inf.readEoln();
  }

  inf.readEof();
}
