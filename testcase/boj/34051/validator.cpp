#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(1, 5000, "N"); inf.readEoln();

  string S = inf.readToken(format("[a-z]{%d}", N), "S");
  inf.readEoln();

  inf.readEof();
}
