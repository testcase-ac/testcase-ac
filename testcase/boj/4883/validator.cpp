#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Multiple test cases, terminated by N = 0
    while (true) {
        // Read N, allow 0 as terminator, or 2..100000 as valid
        int N = inf.readInt(0, 100000, "N");
        inf.readEoln();
        if (N == 0) {
            // End of all test cases
            break;
        }
        // Validate per-problem constraint
        ensuref(N >= 2, "N must be at least 2, but got %d", N);

        // Read N rows, each with 3 integer costs
        for (int i = 0; i < N; i++) {
            // Each cost is integer and cost^2 < 1,000,000 => |cost| < 1000
            vector<int> vals = inf.readInts(3, -999, 999, "cost");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
