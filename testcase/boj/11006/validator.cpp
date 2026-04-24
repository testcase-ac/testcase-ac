#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 25, "T");
    inf.readEoln();

    // Process each test case
    for (int tc = 1; tc <= T; tc++) {
        // Total number of legs
        int N = inf.readInt(1, 300, "N");
        inf.readSpace();
        // Number of chickens
        int M = inf.readInt(1, 300, "M");
        inf.readEoln();

        // Validate the implied constraint M ≤ N ≤ 2M
        ensuref(M <= N,
                "Case %d: number of chickens M (%d) must be ≤ total legs N (%d)",
                tc, M, N);
        ensuref(N <= 2LL * M,
                "Case %d: total legs N (%d) must be ≤ 2 * M (%d)",
                tc, N, 2 * M);
    }

    inf.readEof();
    return 0;
}
