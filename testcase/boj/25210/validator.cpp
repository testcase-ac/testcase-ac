#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int limit = 100000;
    for (int quadrant = 1; quadrant <= 4; ++quadrant) {
        int x1 = inf.readInt(-limit, limit, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-limit, limit, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-limit, limit, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-limit, limit, "y2");
        inf.readEoln();

        ensuref(x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0,
                "quadrant %d has a coordinate on an axis", quadrant);

        if (quadrant == 1) {
            ensuref(0 < x1 && x1 < x2, "invalid x order in quadrant 1: %d %d", x1, x2);
            ensuref(0 < y1 && y1 < y2, "invalid y order in quadrant 1: %d %d", y1, y2);
        } else if (quadrant == 2) {
            ensuref(x2 < x1 && x1 < 0, "invalid x order in quadrant 2: %d %d", x1, x2);
            ensuref(0 < y1 && y1 < y2, "invalid y order in quadrant 2: %d %d", y1, y2);
        } else if (quadrant == 3) {
            ensuref(x2 < x1 && x1 < 0, "invalid x order in quadrant 3: %d %d", x1, x2);
            ensuref(y2 < y1 && y1 < 0, "invalid y order in quadrant 3: %d %d", y1, y2);
        } else {
            ensuref(0 < x1 && x1 < x2, "invalid x order in quadrant 4: %d %d", x1, x2);
            ensuref(y2 < y1 && y1 < 0, "invalid y order in quadrant 4: %d %d", y1, y2);
        }
    }

    inf.readEof();
    return 0;
}
