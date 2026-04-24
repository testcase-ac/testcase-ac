#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read x
    int x = inf.readInt(2, 100, "x");
    // There must be at least one space between x and y
    inf.readSpace();
    // y in [1, 2x-1]
    int y = inf.readInt(1, 2 * x - 1, "y");
    // Implicit constraint: x != y
    ensuref(y != x, "Invalid input: y (%d) must not be equal to x (%d)", y, x);
    // End of line after the only line
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
