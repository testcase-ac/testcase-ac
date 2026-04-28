#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int Q = inf.readInt(1, 3e5, "Q"); inf.readEoln();
  for (int i = 1; i <= Q; i++) {
    inf.readInt(1, 1e9, "x"); inf.readSpace();
    inf.readInt(1, 1e9, "y"); inf.readEoln();
  }
  inf.readEof();
}
