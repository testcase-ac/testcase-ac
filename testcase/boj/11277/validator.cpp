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
    for (int idx = 1; idx <= M; idx++) {
        // Each clause has two literals i and j, with 1 <= |i|,|j| <= N
        int lit1 = inf.readInt(-(long long)N, (long long)N, "i");
        inf.readSpace();
        int lit2 = inf.readInt(-(long long)N, (long long)N, "j");
        inf.readEoln();

        // Neither literal may be zero
        ensuref(lit1 != 0, "Clause %d: first literal is zero", idx);
        ensuref(lit2 != 0, "Clause %d: second literal is zero", idx);
    }

    // No extra data
    inf.readEof();
    return 0;
}
