#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to bias N distribution: -1 for small, 0 for uniform, 1 for large
    int biasMode = rnd.next(-1, 1);
    int N;
    if (biasMode == 0) {
        // uniform between 1 and 10
        N = rnd.next(1, 10);
    } else {
        // weighted: small values if biasMode<0, large if biasMode>0
        // rnd.wnext(10, biasMode) gives [0..9], so +1 -> [1..10]
        N = rnd.wnext(10, biasMode) + 1;
    }

    // Occasionally force even or odd to catch pattern mistakes
    if (rnd.next(0, 1)) {
        if (rnd.next(0, 1)) {
            // make even
            if (N % 2) N = min(10, N + 1);
        } else {
            // make odd
            if (N % 2 == 0) N = max(1, N - 1);
        }
    }

    // Output
    println(N);
    return 0;
}
