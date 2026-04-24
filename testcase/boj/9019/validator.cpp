#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // If you want errors to mention the case number:
        setTestCase(tc);

        // Read A and B for this test case
        int A = inf.readInt(0, 9999, "A");
        inf.readSpace();
        int B = inf.readInt(0, 9999, "B");
        inf.readEoln();

        // A and B must be different
        ensuref(A != B,
                "Test case %d: A and B must differ, but both are %d",
                tc, A);
    }

    inf.readEof();
    return 0;
}
