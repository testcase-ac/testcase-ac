#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 300, "R");
    inf.readSpace();
    int c = inf.readInt(1, 300, "C");
    inf.readSpace();
    int n = inf.readInt(0, 600, "N");
    inf.readEoln();

    ensuref(n <= r * c, "N=%d exceeds board cell count %d", n, r * c);

    set<pair<int, int>> emptyCells;
    for (int i = 0; i < n; ++i) {
        int row = inf.readInt(1, r, "row");
        inf.readSpace();
        int col = inf.readInt(1, c, "col");
        inf.readEoln();

        ensuref(emptyCells.insert({row, col}).second,
                "duplicate empty cell at index %d: (%d, %d)", i + 1, row, col);
    }

    inf.readEof();
}
