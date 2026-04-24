#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and r
    int R = inf.readInt(1, 100000, "R");
    inf.readSpace(); // exactly one whitespace between R and r
    int r = inf.readInt(1, 100000, "r");
    inf.readEoln();

    // Validate the problem constraint 2*r <= R
    ensuref(
        2LL * r <= R,
        "Constraint violation: must have 2*r <= R but got r = %d, R = %d",
        r, R
    );

    // Ensure no extra data
    inf.readEof();
    return 0;
}
