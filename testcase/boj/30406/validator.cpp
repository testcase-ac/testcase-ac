#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(2, 200'000, "N"); inf.readEoln();
  ensuref(N % 2 == 0, "N should be even");

  for (int i = 1; i <= N; i++) {
    int x = inf.readInt(0, 3, "x");

    if (i != N) inf.readSpace();
    else inf.readEoln();
  }

  inf.readEof();
}
