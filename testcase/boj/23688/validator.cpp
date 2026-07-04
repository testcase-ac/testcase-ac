#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int q = inf.readInt(1, 500000, "q");
    inf.readEoln();

    for (int friendIndex = 1; friendIndex <= m; ++friendIndex) {
        vector<int> seen(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            int p = inf.readInt(1, n, "p_i");
            ensuref(!seen[p], "friend %d permutation repeats value %d", friendIndex, p);
            seen[p] = 1;
        }
        inf.readEoln();
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(1, n, "b");
        inf.readEoln();
    }

    inf.readEof();
}
