#include "testlib.h"

#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        for (int quadrant = 1; quadrant <= 4; ++quadrant) {
            int x1 = inf.readInt(-100000, 100000, "x1");
            inf.readSpace();
            int y1 = inf.readInt(-100000, 100000, "y1");
            inf.readSpace();
            int x2 = inf.readInt(-100000, 100000, "x2");
            inf.readSpace();
            int y2 = inf.readInt(-100000, 100000, "y2");
            inf.readEoln();

            ensuref(abs(x1) >= 1 && abs(x2) >= 1,
                    "quadrant %d x-coordinates must be nonzero", quadrant);
            ensuref(abs(y1) >= 1 && abs(y2) >= 1,
                    "quadrant %d y-coordinates must be nonzero", quadrant);

            if (quadrant == 1) {
                ensuref(x1 > 0 && y1 > 0 && x2 > 0 && y2 > 0,
                        "quadrant 1 rectangle must have positive x and y");
                ensuref(x1 < x2 && y1 < y2,
                        "quadrant 1 near corner must be closer to the origin");
            } else if (quadrant == 2) {
                ensuref(x1 < 0 && y1 > 0 && x2 < 0 && y2 > 0,
                        "quadrant 2 rectangle must have negative x and positive y");
                ensuref(x1 > x2 && y1 < y2,
                        "quadrant 2 near corner must be closer to the origin");
            } else if (quadrant == 3) {
                ensuref(x1 < 0 && y1 < 0 && x2 < 0 && y2 < 0,
                        "quadrant 3 rectangle must have negative x and y");
                ensuref(x1 > x2 && y1 > y2,
                        "quadrant 3 near corner must be closer to the origin");
            } else {
                ensuref(x1 > 0 && y1 < 0 && x2 > 0 && y2 < 0,
                        "quadrant 4 rectangle must have positive x and negative y");
                ensuref(x1 < x2 && y1 > y2,
                        "quadrant 4 near corner must be closer to the origin");
            }
        }
    }

    inf.readEof();
}
