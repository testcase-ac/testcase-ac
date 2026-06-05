#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        // CHECK: The statement says each path connects a pair of barns, so loops are rejected.
        ensuref(a != b, "loop at edge index %d: (%d, %d)", i + 1, a, b);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int barn = inf.readInt(1, n, "close_i");
        inf.readEoln();

        ensuref(!seen[barn], "duplicate barn in closing order at index %d: %d", i + 1, barn);
        seen[barn] = true;
    }

    inf.readEof();
}
