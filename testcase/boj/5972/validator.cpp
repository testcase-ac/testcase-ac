#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50000, "M");
    inf.readEoln();

    // Read M edges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int C = inf.readInt(0, 1000, "C_i");
        inf.readEoln();

        // No loops allowed
        ensuref(A != B,
                "Loop detected at edge index %d: (%d, %d)", i, A, B);
        // Multiple edges are allowed by problem statement, so no check here
    }

    inf.readEof();
    return 0;
}
