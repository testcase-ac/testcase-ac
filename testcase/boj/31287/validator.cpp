#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

const int MAXN = 2000, MAXK = 1e9;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  int N = inf.readInt(1, 2000, "N"); inf.readSpace();
  inf.readInt(1, MAXK, "K"); inf.readEoln();

  string S = inf.readToken(format("[UDLR]{%d}", N), "S");
  inf.readEoln();

  inf.readEof();
}
