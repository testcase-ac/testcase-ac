#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lamps
    int N = rnd.next(2, 10);
    // Starting lamp index
    int M = rnd.next(1, N);

    // Choose a pattern for gaps between lamp positions
    int gapType = rnd.next(0, 2);
    int base0 = rnd.next(0, 20);

    vector<long long> D(N + 1), W(N + 1);
    D[1] = base0;
    for (int i = 2; i <= N; i++) {
        int gap;
        if (gapType == 0) {
            // clustered
            gap = rnd.next(1, 5);
        } else if (gapType == 1) {
            // sparse
            gap = rnd.next(50, 100);
        } else {
            // mixed
            gap = rnd.next(1, 100);
        }
        D[i] = D[i - 1] + gap;
    }

    // Weight upper bound and bias for distribution
    int upW = rnd.next(1, 100);
    vector<int> biases = { -1, 0, 1 };
    int weightBias = rnd.any(biases);
    for (int i = 1; i <= N; i++) {
        // rnd.wnext(upW, weightBias) gives [0..upW-1] biased; +1 to get [1..upW]
        W[i] = rnd.wnext(upW, weightBias) + 1;
    }

    // Output
    println(N, M);
    for (int i = 1; i <= N; i++) {
        println(D[i], W[i]);
    }

    return 0;
}
