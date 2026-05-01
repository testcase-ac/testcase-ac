#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: small, medium, or larger but keep overall size manageable
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 30);
    } else {
        N = rnd.next(31, 100);
    }

    // Choose M: sometimes more outlets than devices to test trivial cases
    int M;
    if (N < 10 && rnd.next(0, 4) == 0) {
        // M > N case
        M = rnd.next(N + 1, 10);
    } else {
        M = rnd.next(1, min(N, 10));
    }

    // Bias for time distribution: negative for small, positive for large, zero uniform
    int tBias = rnd.next(-2, 2);
    vector<int> t(N);
    for (int i = 0; i < N; i++) {
        int k = rnd.wnext(16, tBias);  // k in [0,15], biased
        t[i] = 1 << k;
    }

    // Occasionally sort to create ordered edge cases
    if (rnd.next(0, 3) == 0) {
        sort(t.begin(), t.end());
        if (rnd.next(0, 1)) {
            reverse(t.begin(), t.end());
        }
    }

    // Output
    println(N, M);
    println(t);

    return 0;
}
