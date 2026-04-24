#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rectangles
    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    // Read each rectangle
    for (int i = 0; i < n; i++) {
        int ux = inf.readInt(-10000000, 10000000, "u_x");
        inf.readSpace();
        int uy = inf.readInt(-10000000, 10000000, "u_y");
        inf.readSpace();
        int vx = inf.readInt(-10000000, 10000000, "v_x");
        inf.readSpace();
        int vy = inf.readInt(-10000000, 10000000, "v_y");
        inf.readEoln();

        // Validate strict inequalities for proper (non-degenerate) rectangles
        ensuref(ux < vx,
                "Rectangle %d: expected u_x < v_x, but got u_x=%d, v_x=%d",
                i, ux, vx);
        ensuref(uy > vy,
                "Rectangle %d: expected u_y > v_y, but got u_y=%d, v_y=%d",
                i, uy, vy);
    }

    inf.readEof();
    return 0;
}
