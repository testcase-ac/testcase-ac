#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read M, N, x, y with the given constraints
        int M = inf.readInt(1, 40000, "M");
        inf.readSpace();
        int N = inf.readInt(1, 40000, "N");
        inf.readSpace();
        int x = inf.readInt(1, M, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
