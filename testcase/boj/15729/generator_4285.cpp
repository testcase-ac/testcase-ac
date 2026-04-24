#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkable cases
    int N = rnd.next(1, 10);

    // Choose a pattern type for diversity
    int patternType = rnd.next(0, 4);

    vector<int> a(N, 0);

    if (patternType == 0) {
        // Uniform random bits
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(0, 1);
        }
    } else if (patternType == 1) {
        // Clustered runs of 0s and 1s
        int filled = 0;
        int bit = rnd.next(0, 1);
        while (filled < N) {
            int maxRun = N - filled;
            int runLen = rnd.next(1, maxRun);
            for (int j = 0; j < runLen; j++) {
                a[filled++] = bit;
            }
            bit ^= 1;
        }
    } else if (patternType == 2) {
        // Strict alternating pattern
        int start = rnd.next(0, 1);
        for (int i = 0; i < N; i++) {
            a[i] = (start + i) % 2;
        }
    } else if (patternType == 3) {
        // Mostly zeros, tail random
        int prefix = rnd.next(0, N);
        for (int i = prefix; i < N; i++) {
            a[i] = rnd.next(0, 1);
        }
    } else {
        // Few scattered ones
        int maxOnes = max(1, N/4);
        int k = rnd.next(1, maxOnes);
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < k; i++) {
            a[idx[i]] = 1;
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
