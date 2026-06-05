#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 1000000, "y_i");
        inf.readEoln();

        ensuref(x % 2 == 1, "x_%d must be odd, got %d", i + 1, x);
        ensuref(y % 2 == 1, "y_%d must be odd, got %d", i + 1, y);
        ensuref(points.insert({x, y}).second,
                "duplicate cow location at index %d: (%d, %d)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
}
