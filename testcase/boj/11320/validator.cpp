#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Validate each test case
    for (int tc = 1; tc <= T; tc++) {
        // Read A and B
        int A = inf.readInt(1, 1000, "A");
        inf.readSpace();
        int B = inf.readInt(1, A, "B");
        inf.readEoln();

        // Check divisibility constraint
        ensuref(A % B == 0,
                "In test case %d, A must be divisible by B, but got A=%d, B=%d",
                tc, A, B);
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
