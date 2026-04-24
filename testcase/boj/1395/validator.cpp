#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M operations
    for (int i = 1; i <= M; i++) {
        int O = inf.readInt(0, 1, "O_i");
        inf.readSpace();
        int S = inf.readInt(1, N, "S_i");
        inf.readSpace();
        int T = inf.readInt(1, N, "T_i");
        inf.readEoln();

        ensuref(S <= T,
                "Operation %d: S_i (%d) must be <= T_i (%d)",
                i, S, T);
    }

    inf.readEof();
    return 0;
}
