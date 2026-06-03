#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no T bound; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "N");
        inf.readEoln();

        totalN += n;
        // CHECK: The statement gives no total-N bound; keep numeric inputs under the local practical token cap.
        ensuref(totalN <= 2000000, "sum of N exceeds practical cap: %lld", totalN);

        vector<int> x = inf.readInts(n, 1, 100000000, "x_i");
        inf.readEoln();
        for (int i = 1; i < n; ++i) {
            // CHECK: Interprets "in ascending order" as strictly increasing village coordinates.
            ensuref(x[i - 1] < x[i], "x coordinates are not strictly increasing at index %d: %d >= %d",
                    i + 1, x[i - 1], x[i]);
        }

        inf.readInts(n, 1, 10000, "fans_i");
        inf.readEoln();
    }

    inf.readEof();
}
