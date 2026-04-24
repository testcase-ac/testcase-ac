#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M clauses
    for (int idx = 1; idx <= M; idx++) {
        int x = inf.readInt(-N, N, "literal_i");
        inf.readSpace();
        int y = inf.readInt(-N, N, "literal_j");
        inf.readEoln();

        // Literals must be non-zero
        ensuref(x != 0, "Clause %d: first literal is zero", idx);
        ensuref(y != 0, "Clause %d: second literal is zero", idx);
        // After readInt with bounds [-N, N], abs(x), abs(y) <= N is guaranteed
    }

    inf.readEof();
    return 0;
}
