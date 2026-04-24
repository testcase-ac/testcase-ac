#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Upper bound for hand-checkable sizes
    int maxDim = 10;

    // Hyper-parameter: choose shape type
    // 0: single row, 1: single column, 2: square, 3: general
    int type = rnd.next(0, 3);

    int n, m;
    if (type == 0) {
        // single row
        n = 1;
        m = rnd.next(1, maxDim);
    } else if (type == 1) {
        // single column
        m = 1;
        n = rnd.next(1, maxDim);
    } else if (type == 2) {
        // square grid
        n = rnd.next(1, maxDim);
        m = n;
    } else {
        // fully random small grid
        n = rnd.next(1, maxDim);
        m = rnd.next(1, maxDim);
    }

    // Output the test case
    println(n, m);

    return 0;
}
