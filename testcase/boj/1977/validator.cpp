#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M on the first line: natural number between 1 and 10000
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read N on the second line: natural number between 1 and 10000
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Global constraint: M must be <= N
    ensuref(M <= N,
            "Constraint violation: M must be <= N, but M = %d, N = %d",
            M, N);

    // No extra tokens
    inf.readEof();
    return 0;
}
