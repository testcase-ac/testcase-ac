#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The pool is a right isosceles triangle with legs of length 250,
    // placed with vertices at (0,0), (250,0), (0,250).
    // We read one point P = (x, y), which must lie on the boundary
    // of this triangle: on one of the legs or the hypotenuse.

    // Read x and y as integers in [0,250].
    int x = inf.readInt(0, 250, "x");
    inf.readSpace();
    int y = inf.readInt(0, 250, "y");
    inf.readEoln();

    // Check that P is on one of the three edges:
    // 1) bottom leg: y == 0 and 0 <= x <= 250
    // 2) left leg:  x == 0 and 0 <= y <= 250
    // 3) hypotenuse: x + y == 250 and x,y >= 0
    bool onBottom = (y == 0);
    bool onLeft   = (x == 0);
    bool onHyp    = (x + y == 250);
    ensuref(onBottom || onLeft || onHyp,
            "Point (x,y)=(%d,%d) is not on the boundary of the triangle", x, y);

    inf.readEof();
    return 0;
}
