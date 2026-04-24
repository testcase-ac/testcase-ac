#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int N = rnd.next(1, 10);
    // Choose value range [L, R]
    int L = rnd.next(1, 5);
    int rangeLen = rnd.next(0, 20);
    int R = L + rangeLen;
    // Set K relative to max difference plus some extra
    int maxDiff = R - L;
    int extra = rnd.next(0, 5);
    int Kmax = max(1, maxDiff + extra);
    int K = rnd.next(1, Kmax);

    // Generate the sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(L, R);
    }

    // Number of queries
    int maxQ = min(20, N * (N + 1) / 2);
    int M = rnd.next(1, maxQ);

    // Output
    println(N, K);
    println(A);
    println(M);

    // Generate queries of three types for diversity
    for (int i = 0; i < M; i++) {
        int t = rnd.next(0, 2);
        int l, r;
        if (t == 0) {
            // Small interval of length 1 or 2
            l = rnd.next(1, N);
            r = min(N, l + rnd.next(0, 1));
        } else if (t == 1) {
            // Full range
            l = 1; 
            r = N;
        } else {
            // Random interval
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        println(l, r);
    }

    return 0;
}
