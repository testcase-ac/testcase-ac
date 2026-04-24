#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: length of the canvas
    int N = rnd.next(1, 10);

    // Hyper-parameter for K: choose corner cases or random
    int K;
    int typeK = rnd.next(0, 2);
    if (typeK == 0) {
        K = 1;                // minimal stamp width
    } else if (typeK == 1) {
        K = N;                // stamp covers whole canvas
    } else {
        K = rnd.next(1, N);   // arbitrary within [1, N]
    }

    // Hyper-parameter for M: number of colors/stamps
    int M;
    double p = rnd.next();
    if (p < 0.2) {
        M = 1;                                // only one color
    } else if (p < 0.6) {
        M = rnd.next(1, min(5, 20));          // a few colors
    } else {
        M = rnd.next(1, 20);                  // up to 20 colors
    }

    // Output the single test case: N, M, K
    println(N, M, K);

    return 0;
}
