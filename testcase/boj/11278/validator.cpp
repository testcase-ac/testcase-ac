#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read M clauses
    for (int ci = 0; ci < M; ++ci) {
        // First literal
        int lit1 = inf.readInt(-N, N, "lit1");
        ensuref(lit1 != 0, "Clause %d: first literal is zero", ci);
        inf.readSpace();
        // Second literal
        int lit2 = inf.readInt(-N, N, "lit2");
        ensuref(lit2 != 0, "Clause %d: second literal is zero", ci);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
