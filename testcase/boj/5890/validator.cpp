#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readSpace();
    int tractorX = inf.readInt(1, 1000, "tractor_x");
    inf.readSpace();
    int tractorY = inf.readInt(1, 1000, "tractor_y");
    inf.readEoln();

    set<pair<int, int>> hayBales;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 1000, "hay_x");
        inf.readSpace();
        int y = inf.readInt(1, 1000, "hay_y");
        inf.readEoln();

        ensuref(x != tractorX || y != tractorY,
                "hay bale %d is at the tractor location (%d, %d)",
                i + 1, x, y);

        // CHECK: Distinct bale locations are implied by hay bales occupying field points.
        ensuref(hayBales.insert({x, y}).second,
                "duplicate hay bale location at index %d: (%d, %d)",
                i + 1, x, y);
    }

    inf.readEof();
}
