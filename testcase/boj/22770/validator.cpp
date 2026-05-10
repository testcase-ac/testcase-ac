#include "testlib.h"
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int t = 0; t < n; ++t) {
        // Read ellipse A: a1, b1
        int a1 = inf.readInt(1, 100, "a1");
        inf.readSpace();
        int b1 = inf.readInt(1, 100, "b1");
        inf.readEoln();

        // Read ellipse B: a2, b2
        int a2 = inf.readInt(1, 100, "a2");
        inf.readSpace();
        int b2 = inf.readInt(1, 100, "b2");
        inf.readEoln();

        // Check that both ellipses are non-degenerate: a > 0, b > 0 (already checked by readInt)
        // Check that the ellipses are valid (a, b > 0)
        ensuref(a1 > 0 && b1 > 0, "Ellipse A has non-positive axis: a1=%d, b1=%d", a1, b1);
        ensuref(a2 > 0 && b2 > 0, "Ellipse B has non-positive axis: a2=%d, b2=%d", a2, b2);

        // Check that the ellipses are not circles (not required by problem, circles are allowed)
        // Check that the ellipses are not degenerate (a==0 or b==0), already checked

        // The problem guarantees that the focuses of orbit A are on x-axis, and B on y-axis,
        // which is implied by the input format and the coordinate system.
        // No further check is needed for this property.

        // No further global property to check.
    }

    inf.readEof();
}
