#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: sometimes very small, sometimes up to 30
    int N;
    if (rnd.next(0, 1) == 0) {
        N = rnd.next(1, 5);
    } else {
        N = rnd.next(6, 30);
    }

    // Choose a pattern type for diversity
    int pattern = rnd.next(0, 4);
    vector<int> A(N);

    if (pattern == 0) {
        // Completely random values
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(0, 100);
        }
    } else if (pattern == 1) {
        // Blocky: a few blocks of same parity
        int maxBlocks = min(N, 3);
        int blocks = rnd.next(1, maxBlocks);
        vector<int> bsz(blocks, 1);
        int rem = N - blocks;
        for (int i = 0; i < rem; i++) {
            bsz[rnd.next(0, blocks - 1)]++;
        }
        int idx = 0;
        int curP = rnd.next(0, 1);
        for (int b = 0; b < blocks; b++) {
            for (int j = 0; j < bsz[b]; j++) {
                // generate a number with parity curP
                int v = rnd.next(0, 50) * 2 + curP;
                A[idx++] = v;
            }
            // maybe flip parity for next block
            if (rnd.next(0, 1)) curP ^= 1;
        }
    } else if (pattern == 2) {
        // Strict alternating parity
        int startP = rnd.next(0, 1);
        for (int i = 0; i < N; i++) {
            int p = startP ^ (i & 1);
            A[i] = rnd.next(0, 50) * 2 + p;
        }
    } else if (pattern == 3) {
        // Sorted ascending or descending randoms
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(0, 100);
        }
        sort(A.begin(), A.end());
        if (rnd.next(0, 1)) {
            reverse(A.begin(), A.end());
        }
    } else {
        // Palindromic pattern
        for (int i = 0; i <= (N - 1) / 2; i++) {
            int p = rnd.next(0, 1);
            int v = rnd.next(0, 50) * 2 + p;
            A[i] = A[N - 1 - i] = v;
        }
    }

    // Output
    println(N);
    println(A);

    return 0;
}
