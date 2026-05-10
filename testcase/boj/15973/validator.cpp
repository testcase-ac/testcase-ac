#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first rectangle
    long long x1_1 = inf.readLong(-1000000000LL, 1000000000LL, "x1_1");
    inf.readSpace();
    long long y1_1 = inf.readLong(-1000000000LL, 1000000000LL, "y1_1");
    inf.readSpace();
    long long x2_1 = inf.readLong(-1000000000LL, 1000000000LL, "x2_1");
    inf.readSpace();
    long long y2_1 = inf.readLong(-1000000000LL, 1000000000LL, "y2_1");
    inf.readEoln();

    // Validate first rectangle is non-degenerate
    ensuref(x1_1 < x2_1, "For first box, x1_1 (%lld) must be < x2_1 (%lld)", x1_1, x2_1);
    ensuref(y1_1 < y2_1, "For first box, y1_1 (%lld) must be < y2_1 (%lld)", y1_1, y2_1);

    // Read second rectangle
    long long x1_2 = inf.readLong(-1000000000LL, 1000000000LL, "x1_2");
    inf.readSpace();
    long long y1_2 = inf.readLong(-1000000000LL, 1000000000LL, "y1_2");
    inf.readSpace();
    long long x2_2 = inf.readLong(-1000000000LL, 1000000000LL, "x2_2");
    inf.readSpace();
    long long y2_2 = inf.readLong(-1000000000LL, 1000000000LL, "y2_2");
    inf.readEoln();

    // Validate second rectangle is non-degenerate
    ensuref(x1_2 < x2_2, "For second box, x1_2 (%lld) must be < x2_2 (%lld)", x1_2, x2_2);
    ensuref(y1_2 < y2_2, "For second box, y1_2 (%lld) must be < y2_2 (%lld)", y1_2, y2_2);

    // No extra input
    inf.readEof();
    return 0;
}
