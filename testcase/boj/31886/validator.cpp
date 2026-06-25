#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate error position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
