#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose among small, medium, and large N to maximize variability
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // Small N to test edge cases
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        // Medium N
        N = rnd.next(11, 50);
    } else {
        // Large N for performance boundary
        N = rnd.next(51, 100);
    }

    println(N);
    return 0;
}
