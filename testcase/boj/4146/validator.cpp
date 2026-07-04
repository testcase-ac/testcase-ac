#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 20, "Z");
    inf.readEoln();

    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 2000, "N");
        inf.readSpace();
        int w = inf.readInt(1, 50000, "W");
        inf.readSpace();
        int l = inf.readInt(0, w, "L");
        inf.readEoln();

        ensuref(1LL * n * n >= w,
                "W must not exceed the number of cells: N=%d, W=%d",
                n,
                w);

        set<pair<int, int>> badCells;
        for (int i = 1; i <= w; ++i) {
            int row = inf.readInt(1, n, "row");
            inf.readSpace();
            int col = inf.readInt(1, n, "col");
            inf.readEoln();

            ensuref(badCells.insert({row, col}).second,
                    "duplicate bad cell at index %d: (%d, %d)",
                    i,
                    row,
                    col);
        }

        (void)l;
    }

    inf.readEof();
}
