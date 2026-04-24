#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We generate two integers N, M in [1, 300] with several distributions
    int mode = rnd.next(0, 2);
    int N, M;
    if (mode == 0) {
        // Uniform both
        N = rnd.next(1, 300);
        M = rnd.next(1, 300);
    } else if (mode == 1) {
        // One dimension small, other large
        if (rnd.next(0, 1) == 0) {
            N = rnd.next(1, 10);
            M = rnd.next(1, 300);
        } else {
            N = rnd.next(1, 300);
            M = rnd.next(1, 10);
        }
    } else {
        // Skewed: N tends to be large, M tends to be small
        N = rnd.wnext(300, 2) + 1;   // max of 3 samples in [0..299] => high bias
        M = rnd.wnext(300, -2) + 1;  // min of 3 samples in [0..299] => low bias
    }

    // Final check to respect bounds
    N = min(max(N, 1), 300);
    M = min(max(M, 1), 300);

    println(N, M);
    return 0;
}
