#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int r1 = inf.readInt(-5000, 5000, "r1");
  inf.readSpace();
  int c1 = inf.readInt(-5000, 5000, "c1");
  inf.readSpace();
  int r2 = inf.readInt(-5000, 5000, "r2");
  inf.readSpace();
  int c2 = inf.readInt(-5000, 5000, "c2");
  inf.readEoln();
  inf.readEof();

  ensuref(r1 <= r2, "must satisfy r1 <= r2");
  ensuref(c1 <= c2, "must satisfy c1 <= c2");
  ensuref(r2 - r1 <= 49, "must satisfy r2-r1 <= 49");
  ensuref(c2 - c1 <= 49, "must satisfy c2-c1 <= 49");

  return 0;
}