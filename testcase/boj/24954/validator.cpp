#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000, "c_i");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(0, n - 1, "p_i");
        inf.readEoln();

        vector<bool> seen(n + 1, false);
        for (int j = 1; j <= p; ++j) {
            int a = inf.readInt(1, n, "a_j");
            inf.readSpace();
            inf.readInt(1, 1000, "d_j");
            inf.readEoln();

            ensuref(a != i, "discount target equals source potion: i=%d", i);
            ensuref(!seen[a], "duplicate discount target %d for potion %d", a, i);
            seen[a] = true;
        }
    }

    inf.readEof();
}
