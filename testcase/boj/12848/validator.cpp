#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[.@]{" + to_string(m) + "," + to_string(m) + "}", "row");
        inf.readEoln();
    }

    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    vector<int> p(k);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        p[i] = inf.readInt(1, 1000, "p_i");
        // CHECK: The statement says p_i are given in ascending order and are
        // stick types, so duplicate lengths are rejected as not being distinct types.
        ensuref(i == 0 || p[i - 1] < p[i],
                "p_i must be strictly increasing: p[%d]=%d, p[%d]=%d",
                i, p[i - 1], i + 1, p[i]);
    }
    inf.readEoln();

    inf.readEof();
}
