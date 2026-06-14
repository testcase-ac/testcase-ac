#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; use the local default.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500, "N");
        inf.readEoln();

        // CHECK: Keep total scalar input safely below the local practical cap.
        ensuref(totalN <= 4999999 - n,
                "total N across cases exceeds practical cap before case %d", tc);
        totalN += n;

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int value = inf.readInt(1, n, "s_i");
            inf.readEoln();

            ensuref(!seen[value], "duplicate value in case %d at index %d: %d",
                    tc, i, value);
            seen[value] = true;
        }
    }

    inf.readEof();
}
