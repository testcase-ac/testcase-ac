#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M operations: L_i, R_i, X_i
    for (int i = 1; i <= M; i++) {
        int L = inf.readInt(1, N, "L_i");
        inf.readSpace();
        int R = inf.readInt(L, N, "R_i");
        inf.readSpace();
        int X = inf.readInt(-100000, 100000, "X_i");
        inf.readEoln();
    }

    // Read Q
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read Q queries: K, S, T
    for (int i = 1; i <= Q; i++) {
        int K = inf.readInt(1, N, "K_i");
        inf.readSpace();
        int S = inf.readInt(1, M, "S_i");
        inf.readSpace();
        int T = inf.readInt(S, M, "T_i");
        inf.readEoln();
    }

    // End of file
    inf.readEof();
    return 0;
}
