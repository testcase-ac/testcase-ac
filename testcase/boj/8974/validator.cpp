#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B with constraints 1 ≤ A ≤ B ≤ 1000
    int A = inf.readInt(1, 1000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000, "B");
    ensuref(A <= B, "Constraint violated: A (%d) must be ≤ B (%d)", A, B);
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
