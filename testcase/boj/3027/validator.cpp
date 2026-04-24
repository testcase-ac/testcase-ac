#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rectangles
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= N; i++) {
        // Read one rectangle: (x1,y1,z1) and (x2,y2,z2)
        int x1 = inf.readInt(1, 999, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 999, "y1");
        inf.readSpace();
        int z1 = inf.readInt(1, 999, "z1");
        inf.readSpace();
        int x2 = inf.readInt(1, 999, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 999, "y2");
        inf.readSpace();
        int z2 = inf.readInt(1, 999, "z2");
        inf.readEoln();

        // Determine which coordinate is constant (defines the plane)
        bool xe = (x1 == x2);
        bool ye = (y1 == y2);
        bool ze = (z1 == z2);
        int eq_count = (int)xe + (int)ye + (int)ze;
        ensuref(eq_count == 1,
            "Rectangle %d: exactly one dimension must be equal, but got x_eq=%d, y_eq=%d, z_eq=%d",
            i, (int)xe, (int)ye, (int)ze);

        // For the varying axes, lengths must be positive (non-degenerate rectangle)
        if (xe) {
            // Plane is YZ => y and z must vary
            ensuref(y1 != y2,
                "Rectangle %d on YZ-plane is degenerate along Y: y1=y2=%d",
                i, y1);
            ensuref(z1 != z2,
                "Rectangle %d on YZ-plane is degenerate along Z: z1=z2=%d",
                i, z1);
        } else if (ye) {
            // Plane is ZX => z and x must vary
            ensuref(z1 != z2,
                "Rectangle %d on ZX-plane is degenerate along Z: z1=z2=%d",
                i, z1);
            ensuref(x1 != x2,
                "Rectangle %d on ZX-plane is degenerate along X: x1=x2=%d",
                i, x1);
        } else { // ze
            // Plane is XY => x and y must vary
            ensuref(x1 != x2,
                "Rectangle %d on XY-plane is degenerate along X: x1=x2=%d",
                i, x1);
            ensuref(y1 != y2,
                "Rectangle %d on XY-plane is degenerate along Y: y1=y2=%d",
                i, y1);
        }
    }

    inf.readEof();
    return 0;
}
