#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 30, "x");
    inf.readSpace();
    int y = inf.readInt(1, 30, "y");
    inf.readSpace();
    int z = inf.readInt(1, 30, "z");
    inf.readEoln();

    int xp = inf.readInt(0, x, "x_prime");
    inf.readSpace();
    int yp = inf.readInt(0, y, "y_prime");
    inf.readSpace();
    int zp = inf.readInt(0, z, "z_prime");
    inf.readEoln();

    ensuref(zp == z, "student is guaranteed to have at least E, so z_prime must equal z");

    inf.readEof();
}
