#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(2, 200'000, "N"); inf.readSpace();
  int M = inf.readInt(2, 200'000, "M"); inf.readEoln();

  for (int i = 1; i <= N; i++) {
    int K = inf.readInt(2, 10, "K"); inf.readSpace();
    for (int j = 1; j <= K; j++) {
      int B = inf.readInt(1, M, "B");

      if (j != K) inf.readSpace();
      else inf.readEoln();
    }
  }

  inf.readEof();
}
