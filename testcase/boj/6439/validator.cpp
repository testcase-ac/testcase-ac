#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: at least 1, at most 100000 (default assumption)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Each test case: eight integers in [-50, 50]
        int x_start  = inf.readInt(-50, 50, "x_start");
        inf.readSpace();
        int y_start  = inf.readInt(-50, 50, "y_start");
        inf.readSpace();
        int x_end    = inf.readInt(-50, 50, "x_end");
        inf.readSpace();
        int y_end    = inf.readInt(-50, 50, "y_end");
        inf.readSpace();
        int x_left   = inf.readInt(-50, 50, "x_left");
        inf.readSpace();
        int y_top    = inf.readInt(-50, 50, "y_top");
        inf.readSpace();
        int x_right  = inf.readInt(-50, 50, "x_right");
        inf.readSpace();
        int y_bottom = inf.readInt(-50, 50, "y_bottom");

        // End of this test case line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
