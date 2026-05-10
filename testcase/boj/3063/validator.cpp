#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXT = 100000;

    int T = inf.readInt(1, MAXT, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read first rectangle (original poster)
        int x1 = inf.readInt(1, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 10000, "y2");
        inf.readSpace();
        // Read second rectangle (covering poster)
        int x3 = inf.readInt(1, 10000, "x3");
        inf.readSpace();
        int y3 = inf.readInt(1, 10000, "y3");
        inf.readSpace();
        int x4 = inf.readInt(1, 10000, "x4");
        inf.readSpace();
        int y4 = inf.readInt(1, 10000, "y4");
        inf.readEoln();

        // Check strict inequalities for both rectangles
        ensuref(x1 < x2, "Test case %d: x1 must be < x2, got x1=%d, x2=%d", tc, x1, x2);
        ensuref(y1 < y2, "Test case %d: y1 must be < y2, got y1=%d, y2=%d", tc, y1, y2);
        ensuref(x3 < x4, "Test case %d: x3 must be < x4, got x3=%d, x4=%d", tc, x3, x4);
        ensuref(y3 < y4, "Test case %d: y3 must be < y4, got y3=%d, y4=%d", tc, y3, y4);

        // Global property: visible area (original area minus overlap) must be >= 0,
        // but that's guaranteed by geometry; we still compute once to be safe
        long long area1 = 1LL * (x2 - x1) * (y2 - y1);
        long long ox = max(0, min(x2, x4) - max(x1, x3));
        long long oy = max(0, min(y2, y4) - max(y1, y3));
        long long overlap = ox * oy;
        long long visible = area1 - overlap;

        ensuref(visible >= 0, "Test case %d: visible area is negative (%lld)", tc, visible);
    }

    inf.readEof();
}
