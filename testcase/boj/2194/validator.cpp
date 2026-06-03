#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    int a = inf.readInt(1, 10, "A");
    inf.readSpace();
    int b = inf.readInt(1, 10, "B");
    inf.readSpace();
    int k = inf.readInt(0, 100000, "K");
    inf.readEoln();

    ensuref(a <= n, "unit height A=%d exceeds grid height N=%d", a, n);
    ensuref(b <= m, "unit width B=%d exceeds grid width M=%d", b, m);

    set<pair<int, int>> obstacles;
    for (int i = 0; i < k; ++i) {
        int r = inf.readInt(1, n, "obstacle_row");
        inf.readSpace();
        int c = inf.readInt(1, m, "obstacle_col");
        inf.readEoln();

        // CHECK: K is interpreted as the number of installed obstacle cells.
        ensuref(obstacles.insert({r, c}).second,
                "duplicate obstacle at line %d: (%d, %d)", i + 2, r, c);
    }

    int sr = inf.readInt(1, n - a + 1, "start_row");
    inf.readSpace();
    int sc = inf.readInt(1, m - b + 1, "start_col");
    inf.readEoln();

    int er = inf.readInt(1, n - a + 1, "end_row");
    inf.readSpace();
    int ec = inf.readInt(1, m - b + 1, "end_col");
    inf.readEoln();

    ensuref(sr != er || sc != ec, "start and end positions must be different");
    ensuref(!obstacles.count({sr, sc}),
            "start top-left position has an obstacle: (%d, %d)", sr, sc);

    inf.readEof();
    return 0;
}
