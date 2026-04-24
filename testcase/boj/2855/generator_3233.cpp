#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N for hand-checkable
    int N = rnd.next(2, 10);
    vector<long long> A(N);

    // Hyper-parameter: distribution type for A
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // small values
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1LL, 10LL);
    } else if (distType == 1) {
        // large values within safe sum bounds
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(10000000LL, 100000000LL);
    } else {
        // mixed: mostly small, occasional large
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.8)
                A[i] = rnd.next(1LL, 20LL);
            else
                A[i] = rnd.next(10000000LL, 100000000LL);
        }
    }

    // Hyper-parameter: ordering of sequence
    int order = rnd.next(0, 2);
    if (order == 1) {
        sort(A.begin(), A.end());
    } else if (order == 2) {
        sort(A.begin(), A.end(), greater<long long>());
    }
    // else order == 0: keep random order

    // Compute total sum (will be ≤ 1e9)
    long long total = accumulate(A.begin(), A.end(), 0LL);

    // Hyper-parameter: choose S small or large
    long long S;
    if (rnd.next() < 0.5) {
        // small S
        long long hi = min(20LL, total);
        S = rnd.next(1LL, hi);
    } else {
        // large S
        long long lo = max(1LL, total / 2);
        S = rnd.next(lo, total);
    }

    // Output in required format
    println(N, S);
    for (auto x : A) {
        println(x);
    }
    return 0;
}
