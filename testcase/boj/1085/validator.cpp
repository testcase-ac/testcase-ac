#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four integers in order: x, y, w, h
    int x = inf.readInt(1, 1000, "x");
    inf.readSpace();
    int y = inf.readInt(1, 1000, "y");
    inf.readSpace();
    int w = inf.readInt(1, 1000, "w");
    inf.readSpace();
    int h = inf.readInt(1, 1000, "h");
    inf.readEoln();

    // According to constraints, w,h >= 1 but also x <= w-1 and y <= h-1,
    // so w,h must be at least 2
    ensuref(w >= 2, "w must be at least 2 to allow 1 <= x <= w-1, got w=%d", w);
    ensuref(h >= 2, "h must be at least 2 to allow 1 <= y <= h-1, got h=%d", h);

    // Validate dependent constraints
    ensuref(x <= w - 1,
            "x must satisfy 1 <= x <= w-1, got x=%d, w=%d", x, w);
    ensuref(y <= h - 1,
            "y must satisfy 1 <= y <= h-1, got y=%d, h=%d", y, h);

    inf.readEof();
    return 0;
}
