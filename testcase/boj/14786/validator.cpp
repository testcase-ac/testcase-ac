#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, C with their bounds.
    int A = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    // Validate the implied constraint B ≤ A.
    ensuref(B <= A, "Constraint violated: B (%d) must be <= A (%d)", B, A);

    // No extra data.
    inf.readEof();
    return 0;
}
