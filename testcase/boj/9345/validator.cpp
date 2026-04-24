#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N and K
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int K = inf.readInt(1, 50000, "K");
        inf.readEoln();

        // Read K events
        for (int i = 0; i < K; ++i) {
            int Q = inf.readInt(0, 1, "Q");
            inf.readSpace();
            int A = inf.readInt(0, N - 1, "A");
            inf.readSpace();
            int B = inf.readInt(0, N - 1, "B");
            inf.readEoln();

            // Check that A <= B as per constraints
            ensuref(A <= B,
                    "In test case %d, event %d: A (%d) must be <= B (%d)",
                    tc, i + 1, A, B);
        }
    }

    inf.readEof();
    return 0;
}
