#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 100, "R");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-100, 100, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100, 100, "y_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate rice grain position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
