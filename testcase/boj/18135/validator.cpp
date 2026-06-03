#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();
    ensuref(m <= n, "m must not exceed n because each region contains at least one cell");

    vector<int> starts(m), ends(m);
    for (int i = 0; i < m; ++i) {
        starts[i] = inf.readInt(1, n, "a_i");
        inf.readSpace();
        ends[i] = inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(0, 100000, "c_i");
        inf.readEoln();

        ensuref(starts[i] <= ends[i], "region %d must not wrap: [%d, %d]", i + 1, starts[i], ends[i]);
        if (i == 0) {
            ensuref(starts[i] == 1, "region 1 must start at cell 1");
        } else {
            ensuref(starts[i] == ends[i - 1] + 1,
                    "region %d must start immediately after region %d", i + 1, i);
        }
    }
    ensuref(ends.back() == n, "regions must cover through cell n");

    int operations = 0;
    while (true) {
        int op = inf.readInt(0, 2, "op");
        inf.readSpace();
        int x = inf.readInt(0, n, "x");
        inf.readSpace();
        int y = inf.readInt(0, n, "y");

        if (op == 0) {
            ensuref(x == 0 && y == 0, "terminator must be exactly 0 0 0");
            inf.readEoln();
            break;
        }

        ensuref(x >= 1 && y >= 1, "operation positions must be in [1, n]");
        ++operations;
        ensuref(operations <= 200000, "operation count exceeds 200000");

        int start_region = int(upper_bound(starts.begin(), starts.end(), x) - starts.begin()) - 1;
        int end_region = int(upper_bound(starts.begin(), starts.end(), y) - starts.begin()) - 1;
        ensuref(start_region >= 0 && end_region >= 0, "operation endpoints must belong to a region");
        ensuref(!(x > y && start_region == end_region),
                "operation %d visits region %d twice", operations, start_region + 1);

        if (op == 1) {
            inf.readEoln();
        } else {
            inf.readSpace();
            inf.readInt(1, 1000000, "z");
            inf.readEoln();
        }
    }

    inf.readEof();
}
