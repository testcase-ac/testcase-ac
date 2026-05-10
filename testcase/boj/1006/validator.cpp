#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N and W
        int N = inf.readInt(1, 10000, "N");
        inf.readSpace();
        int W = inf.readInt(1, 10000, "W");
        inf.readEoln();

        // Read outer ring enemy counts
        vector<int> outer = inf.readInts(N, 1, 10000, "outer_i");
        inf.readEoln();

        // Read inner ring enemy counts
        vector<int> inner = inf.readInts(N, 1, 10000, "inner_i");
        inf.readEoln();

        // Validate that no section has more enemies than W
        for (int i = 0; i < N; i++) {
            ensuref(outer[i] <= W,
                    "Test case %d: outer[%d] = %d exceeds W = %d",
                    tc, i+1, outer[i], W);
        }
        for (int i = 0; i < N; i++) {
            ensuref(inner[i] <= W,
                    "Test case %d: inner[%d] = %d exceeds W = %d",
                    tc, i+1, inner[i], W);
        }
    }

    inf.readEof();
    return 0;
}
