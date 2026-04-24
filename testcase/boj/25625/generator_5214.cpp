#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: bias for picking x (small, uniform, or large)
    int bias = rnd.next(-1, 1);
    int x;
    if (bias > 0) {
        // bias towards larger x
        x = 2 + rnd.wnext(99, 1);
    } else if (bias < 0) {
        // bias towards smaller x
        x = 2 + rnd.wnext(99, -1);
    } else {
        // uniform
        x = rnd.next(2, 100);
    }

    // Hyperparameter: choose whether y < x or y > x
    bool wantLess = rnd.next(0, 1);
    int y;
    if (wantLess && x > 2) {
        // y in [1, x-1]
        y = rnd.next(1, x - 1);
    } else {
        // y in [x+1, 2x-1]
        y = rnd.next(x + 1, 2 * x - 1);
    }
    // Just in case y == x, fix it
    if (y == x) {
        if (x > 2) y = rnd.next(1, x - 1);
        else y = rnd.next(x + 1, 2 * x - 1);
    }

    // Output the generated test case
    println(x, y);
    return 0;
}
