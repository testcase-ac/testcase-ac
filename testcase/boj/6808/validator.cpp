#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(-1000, 1000, "planet_x");
        inf.readSpace();
        inf.readInt(-1000, 1000, "planet_y");
        inf.readSpace();
        inf.readInt(-1000, 1000, "planet_z");
        inf.readSpace();
        inf.readInt(1, 10000, "v");
        inf.readSpace();
        inf.readInt(1, 100, "r");
        inf.readEoln();
    }

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "waypoint_x");
        inf.readSpace();
        inf.readInt(-1000, 1000, "waypoint_y");
        inf.readSpace();
        inf.readInt(-1000, 1000, "waypoint_z");
        inf.readEoln();
    }

    inf.readInt(1, 50, "D");
    inf.readEoln();
    inf.readEof();
}
