#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, S, T
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int T = inf.readInt(1, N, "T");
    inf.readEoln();

    // Read M directed edges
    for (int i = 1; i <= M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(A != B,
                "Self-loop detected on flight %d: %d -> %d", i, A, B);
    }

    inf.readEof();
    return 0;
}
