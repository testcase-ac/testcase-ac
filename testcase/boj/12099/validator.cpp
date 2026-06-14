#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 5000, "Q");
    inf.readEoln();

    set<int> spicyValues;
    set<int> sweetValues;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 1000000000, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 1000000000, "b_i");
        inf.readEoln();

        ensuref(spicyValues.insert(a).second, "duplicate a value at menu %d: %d", i, a);
        ensuref(sweetValues.insert(b).second, "duplicate b value at menu %d: %d", i, b);
    }

    for (int i = 1; i <= q; ++i) {
        int u = inf.readInt(1, 1000000000, "u_i");
        inf.readSpace();
        int v = inf.readInt(u, 1000000000, "v_i");
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(x, 1000000000, "y_i");
        inf.readEoln();

        ensuref(v <= u + 10000, "query %d has v > u + 10000: u=%d v=%d", i, u, v);
        ensuref(y <= x + 10000, "query %d has y > x + 10000: x=%d y=%d", i, x, y);
    }

    inf.readEof();
}
