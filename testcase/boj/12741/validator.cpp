#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M = X+Y
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "X+Y");
    inf.readEoln();

    // Read heights A_i
    inf.readInts(N, 1, 1000000000, "A");
    inf.readEoln();

    // Read M operations
    for (int i = 0; i < M; i++) {
        int Q = inf.readInt(1, 2, "Q");
        inf.readSpace();
        int L = inf.readInt(1, N, "L");
        inf.readSpace();
        int R = inf.readInt(1, N, "R");
        inf.readEoln();
        ensuref(L <= R,
                "Operation %d: L (%d) must be <= R (%d)",
                i + 1, L, R);
    }

    inf.readEof();
    return 0;
}
