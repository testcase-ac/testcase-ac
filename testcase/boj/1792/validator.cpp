#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    // Each test case: a, b, d
    for (int i = 1; i <= n; i++) {
        int a = inf.readInt(1, 50000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 50000, "b");
        inf.readSpace();
        int d = inf.readInt(1, 50000, "d");
        inf.readEoln();

        ensuref(d <= a,
                "Test case %d: d (%d) must be <= a (%d)", i, d, a);
        ensuref(d <= b,
                "Test case %d: d (%d) must be <= b (%d)", i, d, b);
    }

    inf.readEof();
    return 0;
}
