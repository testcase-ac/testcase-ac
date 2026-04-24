#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N: small or medium for hand-checkability
    int N = rnd.next(0,1) == 0 ? rnd.next(5, 10) : rnd.next(11, 30);
    // Mode for initial array: 0=asc,1=desc,2=random,3=nearly sorted
    int mode = rnd.next(0, 3);
    vector<int> base(N);
    iota(base.begin(), base.end(), 1);
    vector<int> A = base;
    if (mode == 1) {
        reverse(A.begin(), A.end());
    } else if (mode == 2) {
        shuffle(A.begin(), A.end());
    } else if (mode == 3) {
        // nearly sorted: few random swaps
        int swaps = rnd.next(1, max(1, N/2));
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, N-1);
            int y = rnd.next(0, N-1);
            swap(A[x], A[y]);
        }
    }
    // Estimate maximum number of stores in merge sort: N * depth
    int depth = 0, len = 1;
    while (len < N) {
        len <<= 1;
        depth++;
    }
    int maxStores = max(1, N * depth);
    // Decide K mode: small, medium, slight overflow, large overflow
    int kMode = rnd.next(0, 3);
    int K;
    if (kMode == 0) {
        K = rnd.next(1, max(1, N/2));
    } else if (kMode == 1) {
        K = rnd.next(N/2 + 1, maxStores);
    } else if (kMode == 2) {
        K = rnd.next(maxStores + 1, maxStores + rnd.next(1, 10));
    } else {
        K = rnd.next(maxStores + 1, 100000000);
    }
    // Output
    println(N, K);
    println(A);
    return 0;
}
