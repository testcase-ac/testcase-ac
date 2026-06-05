#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give T or total input-size limits; cap the
    // numeric workload under the local primarily-numeric input default.
    const int maxT = 100000;
    const int maxTotalN = 4900000;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        ensuref(totalN <= maxTotalN - n, "sum of N exceeds %d", maxTotalN);
        totalN += n;

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }

            int start = inf.readInt(1, n, "start");
            ensuref(!seen[start], "duplicate start number %d at position %d", start, i);
            seen[start] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
