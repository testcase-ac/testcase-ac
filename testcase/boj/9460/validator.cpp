#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 10000;
    const int maxCoord = 100000000;
    // CHECK: The statement gives no upper bound for T; cap total points to keep
    // primarily numeric inputs below the local practical token-size limit.
    const int maxTotalN = 2000000;

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, maxN, "n");
        inf.readSpace();
        // CHECK: k is only stated to be positive; use the nearby n upper bound
        // as a practical cap while still allowing k to exceed this case's n.
        inf.readInt(1, maxN, "k");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= maxTotalN, "total n exceeds %d", maxTotalN);

        set<int> seenX;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(-maxCoord, maxCoord, "x_i");
            inf.readSpace();
            inf.readInt(-maxCoord, maxCoord, "y_i");
            ensuref(seenX.insert(x).second,
                    "duplicate x-coordinate at point %d: %d", i, x);

            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
