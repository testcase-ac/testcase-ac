#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(1, 4000, "N"); inf.readEoln();

  vector<int> A;
  for (int i = 1; i <= N; i++) {
    int x = inf.readInt(0, (int)1e9, "x");
    A.push_back(x);

    // should be larger than previous with no duplicates
    if (i > 1) ensuref(A[i - 2] < A[i - 1], "A[%d] should be larger than A[%d]", i - 1, i - 2);

    if (i != N) inf.readSpace();
    else inf.readEoln();
  }

  inf.readEof();
}
