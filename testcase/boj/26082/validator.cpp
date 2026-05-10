#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case as per statement
    int A = inf.readInt(1, 1000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    // B is always a multiple of A
    ensuref(B % A == 0, "B must be a multiple of A, but got A=%d, B=%d", A, B);

    // (Implied) WARBOY performance = B/A * C, check it fits in int range (it does),
    // and is positive; optional but safe to assert.
    long long perf = 1LL * (B / A) * C;
    ensuref(perf > 0, "Computed performance must be positive, got %lld", perf);

    inf.readEof();
}
