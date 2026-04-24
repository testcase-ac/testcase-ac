#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three integers A, B, C on one line
    int A = inf.readInt(1, 99, "A");
    inf.readSpace();
    int B = inf.readInt(1, 99, "B");
    inf.readSpace();
    int C = inf.readInt(1, 99, "C");
    inf.readEoln();

    // Check the strict ordering and bounds: 0 < A < B < C < 100
    ensuref(A < B && B < C,
            "Positions must satisfy 0 < A < B < C < 100, got A=%d, B=%d, C=%d",
            A, B, C);
    // A read as >=1 ensures A>0, C read as <=99 ensures C<100.

    inf.readEof();
    return 0;
}
