#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Number of players
        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();
        // Number of operations
        int M = inf.readInt(1, 200000, "M");
        inf.readEoln();

        // Track accumulated points per player to enforce <= 1e9
        vector<long long> points(N + 1, 0);

        for (int i = 0; i < M; i++) {
            // Operation type: R or Q
            string op = inf.readToken("[RQ]", "op");
            ensuref(op == "R" || op == "Q",
                    "Operation must be 'R' or 'Q' at operation index %d, got '%s'",
                    i, op.c_str());
            inf.readSpace();

            // Player index
            int j = inf.readInt(1, N, "j");

            if (op == "R") {
                // Read score obtained
                inf.readSpace();
                long long k = inf.readLong(1LL, 1000000000LL, "k");
                points[j] += k;
                ensuref(points[j] <= 1000000000LL,
                        "Total points of player %d exceed 1e9 at operation %d: %lld",
                        j, i, points[j]);
            }
            // End of this operation line
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
