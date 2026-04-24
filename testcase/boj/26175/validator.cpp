#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four integers: h, r, d_a, d_w
    int h  = inf.readInt(1, 1000, "h");
    inf.readSpace();
    int r  = inf.readInt(1, 1000, "r");
    inf.readSpace();
    int da = inf.readInt(1, 1000, "d_a");
    inf.readSpace();
    int dw = inf.readInt(1, 1000, "d_w");
    // They must all be on the same line
    inf.readEoln();

    // Validate the implied constraint d_a < d_w
    ensuref(da < dw,
            "Constraint violated: d_a (%d) must be strictly less than d_w (%d)", 
            da, dw);

    // No extra content
    inf.readEof();
    return 0;
}
