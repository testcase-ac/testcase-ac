#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readLong(0LL, 1000000000LL, "elevation");
        }
        inf.readEoln();
    }

    int waypointCount = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            waypointCount += inf.readInt(0, 1, "waypoint");
        }
        inf.readEoln();
    }

    // CHECK: the statement defines designated waypoints that must be mutually reachable.
    ensuref(waypointCount >= 1, "at least one waypoint is required");

    inf.readEof();
}
