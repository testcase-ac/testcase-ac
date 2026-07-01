#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int h = inf.readInt(1, 100, "H");
        inf.readSpace();
        int w = inf.readInt(1, 100, "W");
        inf.readSpace();
        int r = inf.readInt(0, 10, "R");
        inf.readEoln();

        set<pair<int, int>> rocks;
        for (int i = 1; i <= r; ++i) {
            int row = inf.readInt(1, h, "r");
            inf.readSpace();
            int col = inf.readInt(1, w, "c");
            inf.readEoln();

            ensuref(!(row == 1 && col == 1),
                    "rock %d is on the start square", i);
            ensuref(!(row == h && col == w),
                    "rock %d is on the destination square", i);
            ensuref(rocks.insert({row, col}).second,
                    "duplicate rock at index %d: (%d, %d)", i, row, col);
        }
    }

    inf.readEof();
}
