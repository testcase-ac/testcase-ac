#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, unspecified upper bound => assume up to 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read six integers per test case: x1, y1, r1, x2, y2, r2
        int x1 = inf.readInt(-10000, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-10000, 10000, "y1");
        inf.readSpace();
        int r1 = inf.readInt(1, 10000, "r1");
        inf.readSpace();
        int x2 = inf.readInt(-10000, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-10000, 10000, "y2");
        inf.readSpace();
        int r2 = inf.readInt(1, 10000, "r2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
