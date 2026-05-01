#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K;

    // 20%: pick from carefully chosen special cases
    if (rnd.next(0, 4) == 0) {
        const int SPECIAL_CNT = 15;
        int specialN[SPECIAL_CNT] = {
            1, 1, 1,        // very small N
            2, 2, 2, 2,     // N = 2 with various K
            9,              // sample 1
            16,             // sample 2
            10, 20,         // multiples and related
            99,             // arbitrary medium
            100000, 99999, 100000 // near/max limits
        };
        int specialK[SPECIAL_CNT] = {
            1, 2, 10,       // N = 1 cases, including zero-answer case
            1, 2, 3, 10,    // N = 2 with differing forbidden digits
            4,              // sample 1
            12,             // sample 2
            10, 10,         // K multiple of 10, f(K)==f(2K)
            95,             // random medium
            1, 100000, 100000 // extremes and equal N,K
        };
        int idx = rnd.next(0, SPECIAL_CNT - 1);
        N = specialN[idx];
        K = specialK[idx];
    } else {
        // 80%: general randomized cases with several modes
        int mode = rnd.next(0, 2); // 0: small, 1: medium, 2: large N

        if (mode == 0) {
            // Small N: good for manual checking and edge behavior
            N = rnd.next(1, 30);
        } else if (mode == 1) {
            // Medium N
            N = rnd.next(5, 200);
        } else {
            // Large N near maximum
            N = rnd.next(50000, 100000);
        }

        int subtype = rnd.next(0, 2);
        if (subtype == 0) {
            // Completely random K
            K = rnd.next(1, 100000);
        } else if (subtype == 1) {
            // K related to N (equal, slightly smaller, or slightly larger)
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                // K = N
                K = N;
            } else if (choice == 1) {
                // K > N when possible, but within bounds
                if (N >= 100000) {
                    K = 100000;
                } else {
                    int hi = N + 1000;
                    if (hi > 100000) hi = 100000;
                    int lo = N + 1;
                    if (lo > hi) lo = hi;
                    K = rnd.next(lo, hi);
                }
            } else {
                // K <= N, near N
                int lo = (N > 1000 ? N - 1000 : 1);
                int hi = N;
                if (lo > hi) lo = hi;
                K = rnd.next(lo, hi);
            }
        } else {
            // K multiple of 10 so that f(K) == f(2K) (both 0)
            int base = rnd.next(1, 10000); // up to 100000
            long long cand = 1LL * base * 10;
            if (cand > 100000) cand = 100000;
            K = (int)cand;
        }
    }

    println(N, K);
    return 0;
}
