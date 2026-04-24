#include "testlib.h"
#include <cstdio>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, Q
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // Read the fish counts A[i][j]
    char buf[64];
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            std::sprintf(buf, "A_%d_%d", i, j);
            inf.readInt(0, 500, buf);
            if (j < M) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Read the Q queries (W_i, P_i)
    for (int i = 1; i <= Q; i++) {
        std::sprintf(buf, "W_%d", i);
        inf.readInt(1, N, buf);
        inf.readSpace();
        std::sprintf(buf, "P_%d", i);
        inf.readInt(1, M, buf);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
