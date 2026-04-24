#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T, which must be exactly 1.
    int T = inf.readInt(1, 1, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, M, K
        int N = inf.readInt(2, 100, "N");
        inf.readSpace();
        int M = inf.readInt(0, 10000, "M");
        inf.readSpace();
        int K = inf.readInt(0, 10000, "K");
        inf.readEoln();

        // If budget is zero, there must be no tickets (since each ticket cost >= 1).
        ensuref(M > 0 || K == 0,
                "Budget M is 0 but number of tickets K is %d (must be 0 when M=0)", K);

        // Read K ticket lines
        for (int i = 0; i < K; i++) {
            int u = inf.readInt(1, N, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, N, "v_i");
            ensuref(u != v,
                    "Loop detected on ticket %d: u = %d, v = %d (must have u != v)", i, u, v);
            inf.readSpace();
            // cost c: 1 <= c <= M
            int c = inf.readInt(1, M, "c_i");
            inf.readSpace();
            int d = inf.readInt(1, 1000, "d_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
