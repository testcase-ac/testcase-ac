#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "B_i");
    }
    inf.readEoln();

    set<int> seenX;
    set<int> seenY;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "X_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y_i");
        inf.readEoln();

        ensuref(seenX.insert(x).second, "duplicate known position X=%d", x);
        ensuref(seenY.insert(y).second, "duplicate known value Y=%d", y);
    }

    inf.readEof();
}
