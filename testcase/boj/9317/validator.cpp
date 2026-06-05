#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr double MAX_D = 1000000.0;
    constexpr int MAX_RESOLUTION = 1000000000;
    constexpr int MAX_CASES = 100000;

    int cases = 0;
    while (true) {
        // CHECK: The statement gives no numeric bounds; these practical caps keep
        // inputs finite while accepting ordinary monitor sizes and resolutions.
        double d = inf.readStrictDouble(0.0, MAX_D, 0, 10, "D");
        inf.readSpace();
        int horizontal = inf.readInt(0, MAX_RESOLUTION, "Resolution_Horizontal");
        inf.readSpace();
        int vertical = inf.readInt(0, MAX_RESOLUTION, "Resolution_Vertical");
        inf.readEoln();

        if (d == 0.0 && horizontal == 0 && vertical == 0) {
            break;
        }

        ensuref(d > 0.0, "D must be positive before the terminator");
        ensuref(horizontal > 0, "horizontal resolution must be positive before the terminator");
        ensuref(vertical > 0, "vertical resolution must be positive before the terminator");

        ++cases;
        ensuref(cases <= MAX_CASES, "too many monitor descriptions: %d", cases);
    }

    inf.readEof();
}
