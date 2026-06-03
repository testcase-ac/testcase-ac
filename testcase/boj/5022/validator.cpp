#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < 4; ++i) {
        int x = inf.readInt(0, n, "x");
        inf.readSpace();
        int y = inf.readInt(0, m, "y");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
