#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<pair<int, int>> points;
    for (int i = 0; i < 4; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int x = inf.readInt(-10000, 10000, format("x_%d", i + 1));
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, format("y_%d", i + 1));

        ensuref(points.insert({x, y}).second,
                "duplicate point at index %d: (%d, %d)", i + 1, x, y);
    }
    inf.readEoln();
    inf.readEof();
}
