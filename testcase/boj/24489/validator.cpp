#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(0, 200000, "Q");
    inf.readEoln();

    vector<bool> active(n + 1, true);
    vector<bool> removedRoad(1, false);

    for (int i = 1; i <= q; ++i) {
        string type = inf.readToken("A|D|R", "type");

        if (type == "D") {
            inf.readSpace();
            int x = inf.readInt(1, n, "x");
            inf.readEoln();

            ensuref(active[x], "operation %d deactivates inactive farm %d", i, x);
            active[x] = false;
        } else if (type == "A") {
            inf.readSpace();
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readEoln();

            // CHECK: "between two active farms x and y" is interpreted as two distinct farms.
            ensuref(x != y, "operation %d adds a self-loop at farm %d", i, x);
            ensuref(active[x], "operation %d adds a road from inactive farm %d", i, x);
            ensuref(active[y], "operation %d adds a road to inactive farm %d", i, y);
            // CHECK: Parallel roads are allowed; the statement indexes each added road
            // and does not require endpoint pairs to be unique.
            removedRoad.push_back(false);
        } else {
            inf.readSpace();
            int e = inf.readInt(1, (int)removedRoad.size() - 1, "e");
            inf.readEoln();

            ensuref(!removedRoad[e], "operation %d removes road %d more than once", i, e);
            removedRoad[e] = true;
        }
    }

    inf.readEof();
}
