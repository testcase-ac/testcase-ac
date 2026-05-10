#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read house coordinates
    vector<int> X = inf.readInts(N, 1, 1000000000, "X_i");
    inf.readEoln();
    // Check strictly increasing
    for (int i = 0; i + 1 < N; i++) {
        ensuref(X[i] < X[i+1],
                "X_i not strictly increasing at indices %d and %d: %d >= %d",
                i+1, i+2, X[i], X[i+1]);
    }

    // Read queries
    for (int i = 1; i <= Q; i++) {
        int L = inf.readInt(1, 1000000000, "L_i");
        inf.readSpace();
        int R = inf.readInt(1, 1000000000, "R_i");
        inf.readEoln();
        ensuref(L <= R,
                "Query %d has L_i > R_i: %d > %d", i, L, R);
    }

    inf.readEof();
    return 0;
}
