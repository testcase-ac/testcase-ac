#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose N biased towards small, medium, or large
    double p = rnd.next();
    int N;
    if (p < 0.2) {
        // small N to test trivial cases
        N = rnd.next(1, 3);
    } else if (p < 0.5) {
        // medium-small N
        N = rnd.next(4, 10);
    } else if (p < 0.8) {
        // medium-large N
        N = rnd.next(11, 17);
    } else if (p < 0.95) {
        // large N but not maximum
        N = rnd.next(18, 19);
    } else {
        // maximum edge case
        N = 20;
    }
    // Output single integer N
    println(N);
    return 0;
}
