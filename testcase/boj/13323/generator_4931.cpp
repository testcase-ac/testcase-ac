#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkable cases
    int N = rnd.next(1, 10);
    vector<long long> A(N);

    // Choose a pattern type for diversity
    int pat = rnd.next(0, 4);
    if (pat == 0) {
        // Pure random small values
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, 100);
    }
    else if (pat == 1) {
        // Ascending trend with noise
        long long K = rnd.next(0, 5);
        for (int i = 0; i < N; i++) {
            long long v = i * K + rnd.next(-10, 10);
            if (v < 0) v = 0;
            A[i] = v;
        }
    }
    else if (pat == 2) {
        // Descending trend with noise
        long long K = rnd.next(0, 5);
        for (int i = 0; i < N; i++) {
            long long v = (N - 1 - i) * K + rnd.next(-10, 10);
            if (v < 0) v = 0;
            A[i] = v;
        }
    }
    else if (pat == 3) {
        // Constant segments
        double segProb = rnd.next() * 0.8 + 0.1; // between 0.1 and 0.9
        long long cur = rnd.next(0, 100);
        for (int i = 0; i < N; i++) {
            if (i == 0 || rnd.next() < segProb) {
                cur = rnd.next(0, 100);
            }
            A[i] = cur;
        }
    }
    else {
        // High values near the 32-bit upper limit
        int lo = 2000000000 - 1000;
        int hi = 2000000000;
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(lo, hi);
    }

    // Output in the required format
    println(N);
    println(A);

    return 0;
}
