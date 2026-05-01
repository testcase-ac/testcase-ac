#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for number of sticks N: biased small or large
    int tN = rnd.next(-2, 2);
    int N = rnd.wnext(15, tN) + 1;  // N in [1..15]
    // Hyperparameter for maximum stick length
    int tL = rnd.next(-3, 3);
    int maxL = rnd.wnext(100, tL) + 1;  // maxL in [1..100]
    vector<int> L(N);
    for (int i = 0; i < N; i++) {
        // Bias some sticks to be small or large
        int t = rnd.next(-2, 2);
        int li = rnd.wnext(maxL, t) + 1;
        L[i] = li;
    }
    // Shuffle sticks for randomness
    shuffle(L.begin(), L.end());
    // Compute total segments if length = 1
    int totalSegments = accumulate(L.begin(), L.end(), 0);
    // Decide M (number of kids)
    double p = rnd.next();
    int M;
    if (p < 0.4) {
        // Mostly solvable cases
        if (rnd.next(0, 3) == 0) {
            M = 1;
        } else {
            M = rnd.next(1, max(1, totalSegments));
        }
    } else if (p < 0.8) {
        // Force unsolvable (M > totalSegments)
        M = totalSegments + rnd.next(1, totalSegments + 1);
    } else {
        // Edge near boundaries
        int lo = max(1, totalSegments - 10);
        int hi = totalSegments + 10;
        M = rnd.next(lo, hi);
    }
    // Clamp M within problem constraints
    M = min(M, 1000000);
    println(M, N);
    println(L);
    return 0;
}
