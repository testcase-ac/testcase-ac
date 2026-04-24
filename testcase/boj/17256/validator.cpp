#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read cake number a: a.x, a.y, a.z
    int ax = inf.readInt(1, 100, "a.x");
    inf.readSpace();
    int ay = inf.readInt(1, 100, "a.y");
    inf.readSpace();
    int az = inf.readInt(1, 100, "a.z");
    inf.readEoln();

    // Read cake number c: c.x, c.y, c.z
    int cx = inf.readInt(1, 100, "c.x");
    inf.readSpace();
    int cy = inf.readInt(1, 100, "c.y");
    inf.readSpace();
    int cz = inf.readInt(1, 100, "c.z");
    inf.readEoln();

    // Compute b from equations:
    //   c.x = a.z + b.x  -> b.x = c.x - a.z
    //   c.y = a.y * b.y  -> b.y = c.y / a.y, require c.y % a.y == 0
    //   c.z = a.x + b.z  -> b.z = c.z - a.x
    int bx = cx - az;
    ensuref(bx >= 1 && bx <= 100,
            "Computed b.x out of range: b.x = c.x - a.z = %d - %d = %d, but must be in [1,100]",
            cx, az, bx);

    ensuref(ay != 0, "Invalid a.y = 0"); // defensive, though ay>=1 by range
    ensuref(cy % ay == 0,
            "c.y = %d is not divisible by a.y = %d, so b.y is not integer",
            cy, ay);
    int by = cy / ay;
    ensuref(by >= 1 && by <= 100,
            "Computed b.y out of range: b.y = c.y / a.y = %d / %d = %d, but must be in [1,100]",
            cy, ay, by);

    int bz = cz - ax;
    ensuref(bz >= 1 && bz <= 100,
            "Computed b.z out of range: b.z = c.z - a.x = %d - %d = %d, but must be in [1,100]",
            cz, ax, bz);

    // No extra data
    inf.readEof();
    return 0;
}
