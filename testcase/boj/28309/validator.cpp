#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 1000000, "R");
        inf.readSpace();
        int c = inf.readInt(1, 1000000, "C");
        inf.readSpace();
        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        set<pair<int, int>> snacks;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(1, r, "X_i");
            inf.readSpace();
            int y = inf.readInt(1, c, "Y_i");
            inf.readEoln();

            ensuref(!(x == 1 && y == 1),
                    "snack %d is on the start cell (1, 1)", i);
            ensuref(!(x == r && y == c),
                    "snack %d is on the end cell (%d, %d)", i, r, c);
            ensuref(snacks.emplace(x, y).second,
                    "duplicate snack cell at index %d: (%d, %d)", i, x, y);
        }
    }

    inf.readEof();
}
