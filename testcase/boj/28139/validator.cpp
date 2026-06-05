#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5000, "n");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%d, %d)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
}
