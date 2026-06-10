#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int c = inf.readInt(1, n, "C");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 100000, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, 100000, "Y_i");
        inf.readSpace();
        int v = inf.readInt(1, 100000000, "V_i");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "mineral %d is at (0, 0)", i);
        ensuref(positions.insert({x, y}).second,
                "duplicate mineral position at index %d: (%d, %d)", i, x, y);
        (void)v;
    }

    inf.readEof();
}
