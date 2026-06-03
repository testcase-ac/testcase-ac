#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-10000, 10000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "Y_i");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "student %d is at the origin", i + 1);
        ensuref(points.insert({x, y}).second,
                "duplicate student position at index %d: (%d, %d)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
    return 0;
}
