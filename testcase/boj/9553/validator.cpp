#include "testlib.h"

using namespace std;

static long long cross(long long ax, long long ay, long long bx, long long by) {
    return ax * by - ay * bx;
}

static bool segmentContainsOrigin(int x1, int y1, int x2, int y2) {
    if (cross(x1, y1, x2, y2) != 0) {
        return false;
    }
    return min(x1, x2) <= 0 && 0 <= max(x1, x2) &&
           min(y1, y2) <= 0 && 0 <= max(y1, y2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            int x1 = inf.readInt(-100, 100, "X_1");
            inf.readSpace();
            int y1 = inf.readInt(-100, 100, "Y_1");
            inf.readSpace();
            int x2 = inf.readInt(-100, 100, "X_2");
            inf.readSpace();
            int y2 = inf.readInt(-100, 100, "Y_2");
            inf.readEoln();

            ensuref(!segmentContainsOrigin(x1, y1, x2, y2),
                    "target %d intersects the origin: (%d, %d)-(%d, %d)",
                    i, x1, y1, x2, y2);
        }
    }

    inf.readEof();
}
