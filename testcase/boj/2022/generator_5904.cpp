#include "testlib.h"
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose scale of ladder lengths
    int scaleType = rnd.next(1, 4);
    double x, y;
    if (scaleType == 1) {
        // small ladders
        x = rnd.next(1.0, 10.0);
        y = rnd.next(1.0, 10.0);
    } else if (scaleType == 2) {
        // medium ladders
        x = rnd.next(10.0, 100.0);
        y = rnd.next(10.0, 100.0);
    } else if (scaleType == 3) {
        // large ladders
        x = rnd.next(100.0, 1000.0);
        y = rnd.next(100.0, 1000.0);
    } else {
        // extra-large ladders
        x = rnd.next(1000.0, 10000.0);
        y = rnd.next(1000.0, 10000.0);
    }
    // occasionally make ladders equal length
    if (rnd.next(0, 3) == 0) {
        y = x;
    }
    // ensure random order
    if (rnd.next(0,1) == 0) {
        swap(x, y);
    }
    // choose crossing height c such that 0 < c < min(x,y)
    double minxy = min(x, y);
    double eps = 1e-6;
    double c;
    // occasionally very small c
    if (rnd.next(0, 5) == 0) {
        double hi = min(0.1, minxy - eps);
        c = rnd.next(eps, hi);
    }
    // occasionally c very close to min(x,y)
    else if (rnd.next(0, 5) == 0) {
        double hi = min(1.0, minxy - eps);
        c = minxy - rnd.next(eps, hi);
    }
    // general case
    else {
        c = rnd.next(eps, minxy - eps);
    }
    // output with six decimal places
    printf("%.6f %.6f %.6f\n", x, y, c);
    return 0;
}
