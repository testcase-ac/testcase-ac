#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 200000, "N");
  inf.readSpace();
  int k = inf.readInt(1, 200000, "K");
  inf.readEoln();

  int t = inf.readInt(1, 200000, "T");
  inf.readEoln();

  for (int i = 1; i <= t; ++i) {
    int l = inf.readInt(1, n, "l_i");
    inf.readSpace();
    int r = inf.readInt(l, n, "r_i");
    inf.readSpace();
    inf.readInt(1, k, "x_i");
    inf.readEoln();
  }

  inf.readEof();
}
