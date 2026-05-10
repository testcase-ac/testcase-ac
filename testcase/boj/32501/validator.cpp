#include "testlib.h"
#include <cmath>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read input line
    int x1 = inf.readInt(-100, 100, "x1");
    inf.readSpace();
    int y1 = inf.readInt(-100, 100, "y1");
    inf.readSpace();
    int x2 = inf.readInt(-100, 100, "x2");
    inf.readSpace();
    int y2 = inf.readInt(-100, 100, "y2");
    inf.readSpace();
    int a = inf.readInt(0, 1000, "a"); // lower bound checked below
    inf.readEoln();

    // Compute distance between foci
    double dx = x2 - x1;
    double dy = y2 - y1;
    double foci_dist = sqrt(dx * dx + dy * dy);

    // Check that a >= foci_dist
    ensuref(a >= foci_dist - 1e-8, 
        "Major axis length a = %d is less than distance between foci = %.10lf", a, foci_dist);

    // Check that a > 0 (ellipse must be non-degenerate)
    ensuref(a > 0, "Major axis length a must be positive, got %d", a);

    // Check that a <= 1000 (already checked by readInt)

    inf.readEof();
}
