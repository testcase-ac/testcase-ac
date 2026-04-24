#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a bias mode for N to get diverse sizes
    int mode = rnd.next(-2, 2);
    int N;
    if (mode == -2) {
        // Very small
        N = rnd.next(2, 15);
    } else if (mode == -1) {
        // Small
        N = rnd.next(16, 100);
    } else if (mode == 0) {
        // Medium
        N = rnd.next(101, 1000);
    } else if (mode == 1) {
        // Large
        N = rnd.next(1000, 10000);
    } else {
        // Very large (up to the max constraint)
        N = rnd.next(10000, 20000);
    }

    println(N);
    return 0;
}
