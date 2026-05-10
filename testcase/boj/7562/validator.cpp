#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases (not specified, so assume up to 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Board size l, 4 ≤ l ≤ 300
        int l = inf.readInt(4, 300, "l");
        inf.readEoln();

        // Starting position (x1, y1)
        int x1 = inf.readInt(0, l - 1, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, l - 1, "y1");
        inf.readEoln();

        // Target position (x2, y2)
        int x2 = inf.readInt(0, l - 1, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, l - 1, "y2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
