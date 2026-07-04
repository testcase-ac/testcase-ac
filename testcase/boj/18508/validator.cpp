#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "n");
    inf.readEoln();
    ensuref(n % 2 == 0, "n must be even, got %d", n);

    set<pair<int, int>> points;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
    return 0;
}
