#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions and number of operations
    int N = inf.readInt(3, 50, "N");
    inf.readSpace();
    int M = inf.readInt(3, 50, "M");
    inf.readSpace();
    int K = inf.readInt(1, 6, "K");
    inf.readEoln();

    // Read the array A
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            inf.readInt(1, 100, "A_i_j");
            if (j < M)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }

    // Read the K operations
    for (int i = 1; i <= K; i++) {
        int r = inf.readInt(1, N, "r");
        inf.readSpace();
        int c = inf.readInt(1, M, "c");
        inf.readSpace();
        // s must be at least 1; upper bound large enough to be caught by relation checks
        int s = inf.readInt(1, max(N, M), "s");
        inf.readEoln();

        // Validate the rotation square fits inside the array
        ensuref(r - s >= 1, "Operation %d: r - s < 1 (r=%d, s=%d)", i, r, s);
        ensuref(r + s <= N, "Operation %d: r + s > N (r=%d, s=%d, N=%d)", i, r, s, N);
        ensuref(c - s >= 1, "Operation %d: c - s < 1 (c=%d, s=%d)", i, c, s);
        ensuref(c + s <= M, "Operation %d: c + s > M (c=%d, s=%d, M=%d)", i, c, s, M);
    }

    inf.readEof();
    return 0;
}
