#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int b = inf.readInt(1, 1000000, "B");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, b, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, b, "y_i");
        inf.readEoln();

        ensuref(x % 2 == 1, "x_%d must be odd, found %d", i, x);
        ensuref(y % 2 == 1, "y_%d must be odd, found %d", i, y);
        ensuref(seen.insert({x, y}).second,
                "duplicate cow location at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
