#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // 2. Read W and N
        int W = inf.readInt(1, 1000, "W");
        inf.readSpace();
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // 3. Read N lines: x_i, w_i
        vector<int> x(N), w(N);
        set<int> x_set;
        int prev_x = -1;
        for (int i = 0; i < N; ++i) {
            x[i] = inf.readInt(0, 100000, "x_i");
            inf.readSpace();
            w[i] = inf.readInt(1, W, "w_i");
            inf.readEoln();

            // x_i must be unique
            ensuref(x_set.count(x[i]) == 0, "x_i not unique at index %d: %d", i+1, x[i]);
            x_set.insert(x[i]);
            // x_i must be strictly increasing
            if (i > 0) {
                ensuref(x[i] > prev_x, "x_i not strictly increasing at index %d: %d <= %d", i+1, x[i], prev_x);
            }
            prev_x = x[i];
        }

        // 4. Simulate the process to check global properties
        // - All w_i <= W (already checked)
        // - All x_i unique and strictly increasing (already checked)
        // - No further global property is implied by the statement
        // - All w_i >= 1 (already checked)
        // - All x_i >= 0 (already checked)
        // - All x_i <= 100000 (already checked)
        // - All w_i <= W (already checked)
        // - No leading zeros (readInt ensures this)

        // No further simulation is needed, as the problem does not guarantee e.g. "the answer is at most X" or "the answer always exists" (the only possible issue is w_i > W, which is forbidden by constraints).

        // No extra whitespace allowed between test cases
    }

    inf.readEof();
}
