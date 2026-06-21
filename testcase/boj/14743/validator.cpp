#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readSpace();
    int y1 = inf.readInt(-1000000000, 1000000000, "y1");
    inf.readSpace();
    int y2 = inf.readInt(-1000000000, 1000000000, "y2");
    inf.readEoln();

    ensuref(y1 != y2, "y1 and y2 must be different: %d", y1);

    set<int> top;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "top_x");
        inf.readEoln();
        ensuref(top.insert(x).second, "duplicate top x-coordinate at index %d: %d", i + 1, x);
    }

    set<int> bottom;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "bottom_x");
        inf.readEoln();
        ensuref(bottom.insert(x).second, "duplicate bottom x-coordinate at index %d: %d", i + 1, x);
    }

    inf.readEof();
}
