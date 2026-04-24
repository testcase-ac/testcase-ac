#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of sequence
    int N = rnd.next(1, 20);
    // Value range lower bound
    int lo = rnd.next(1, 1000 - N + 1);
    // Ensure enough room for strictly increasing/decreasing of length N
    int hiMin = lo + N - 1;
    int hi = rnd.next(hiMin, 1000);

    // Choose a pattern for diversity
    int mode = rnd.next(1, 5);
    vector<int> A(N);

    if (mode == 1) {
        // Strictly increasing
        int start = rnd.next(lo, hi - (N - 1));
        for (int i = 0; i < N; i++)
            A[i] = start + i;
    } else if (mode == 2) {
        // Strictly decreasing
        int start = rnd.next(lo + (N - 1), hi);
        for (int i = 0; i < N; i++)
            A[i] = start - i;
    } else if (mode == 3) {
        // Uniform random in [lo, hi]
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(lo, hi);
    } else if (mode == 4) {
        // Bitonic: increase to a peak then decrease
        int peak = rnd.next(0, N - 1);
        // increasing part
        int start = rnd.next(lo, hiMin - (N - 1)); // safe start
        for (int i = 0; i <= peak; i++)
            A[i] = start + i;
        // decreasing tail
        for (int i = peak + 1; i < N; i++) {
            int prev = A[i - 1];
            int maxDec = prev - lo;
            if (maxDec <= 1) {
                A[i] = prev - 1;
            } else {
                A[i] = prev - rnd.next(1, maxDec);
            }
        }
    } else {
        // Duplicates-heavy: pick small set of values then sample
        int K = rnd.next(1, min(N, 5));
        vector<int> base;
        // pick K distinct values
        while ((int)base.size() < K) {
            int v = rnd.next(lo, hi);
            bool ok = true;
            for (int x : base)
                if (x == v) { ok = false; break; }
            if (ok) base.push_back(v);
        }
        // fill A by random choice from base
        for (int i = 0; i < N; i++)
            A[i] = rnd.any(base);
    }

    // Final shuffle in random modes to add unpredictability
    if (mode == 3 || mode == 5) {
        shuffle(A.begin(), A.end());
    }

    // Output
    println(N);
    println(A);

    return 0;
}
