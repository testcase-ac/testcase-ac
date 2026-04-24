#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read rectangle coordinates
        int xmin = inf.readInt(-10000, 10000, "xmin");
        inf.readSpace();
        int ymin = inf.readInt(-10000, 10000, "ymin");
        inf.readSpace();
        int xmax = inf.readInt(-10000, 10000, "xmax");
        inf.readSpace();
        int ymax = inf.readInt(-10000, 10000, "ymax");
        inf.readEoln();

        // Validate rectangle
        ensuref(xmin < xmax,
                "Test case %d: xmin (%d) must be less than xmax (%d)", 
                tc, xmin, xmax);
        ensuref(ymin < ymax,
                "Test case %d: ymin (%d) must be less than ymax (%d)", 
                tc, ymin, ymax);

        // Read segment endpoints
        int x1 = inf.readInt(-10000, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-10000, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-10000, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-10000, 10000, "y2");
        inf.readEoln();

        // Validate segment has positive length
        ensuref(!(x1 == x2 && y1 == y2),
                "Test case %d: segment endpoints must be distinct, got (%d,%d) and (%d,%d)",
                tc, x1, y1, x2, y2);
    }

    inf.readEof();
    return 0;
}
