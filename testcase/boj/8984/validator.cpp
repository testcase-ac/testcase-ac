#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 100000, "N");
  inf.readSpace();
  inf.readInt(1, 1000000, "L");
  inf.readEoln();

  set<pair<int, int>> sticks;
  for (int i = 0; i < n; ++i) {
    int t = inf.readInt(0, 100000000, "t");
    inf.readSpace();
    int d = inf.readInt(0, 100000000, "d");
    inf.readEoln();

    ensuref(sticks.insert({t, d}).second,
            "duplicate stick at index %d: (%d, %d)", i + 1, t, d);
  }

  inf.readEof();
}
