#include "testlib.h"
#include <cmath>
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
        int a = inf.readInt(-N, N, "literal1");
        inf.readSpace();
        int b = inf.readInt(-N, N, "literal2");
        inf.readEoln();

        ensuref(a != 0, "Clause %d first literal is zero", idx);
        ensuref(b != 0, "Clause %d second literal is zero", idx);
        // abs(a) and abs(b) are guaranteed <= N by readInt bounds
    }

    inf.readEof();
    return 0;
}
