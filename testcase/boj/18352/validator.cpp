#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K, X
    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 300000, "K");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readEoln();

    // Read M directed edges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        // No self loops allowed (A != B)
        ensuref(A != B, "Self-loop detected at edge %d: (%d -> %d)", i+1, A, B);
    }

    inf.readEof();
    return 0;
}
