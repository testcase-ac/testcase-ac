#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> coverage(n + 1, 0);
    int prev_a = -1;
    int prev_b = -1;

    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(a, n - 1, "b_i");
        inf.readEoln();

        ++coverage[a];
        --coverage[b + 1];

        if (i > 0) {
            int overlap = min(prev_b, b) - max(prev_a, a) + 1;
            // CHECK: the hint says consecutive rows share at least two columns,
            // but the official samples include consecutive rows sharing one.
            ensuref(overlap >= 1,
                    "rows %d and %d do not share a non-blurred column",
                    i, i + 1, max(0, overlap));
        }

        prev_a = a;
        prev_b = b;
    }

    int active = 0;
    for (int col = 0; col < n; ++col) {
        active += coverage[col];
        ensuref(active > 0, "column %d has no non-blurred pixel", col);
    }

    inf.readEof();
}
