#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N with constraints 1 ≤ M ≤ N ≤ 99
    int M = inf.readInt(1, 99, "M");
    inf.readSpace();
    int N = inf.readInt(1, 99, "N");
    ensuref(M <= N, "Constraint violation: M (%d) must be ≤ N (%d)", M, N);

    // End of the only line
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
