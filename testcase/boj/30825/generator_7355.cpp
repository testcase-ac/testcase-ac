#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose sequence length N in small, medium, or larger range
    int sizeType = rnd.next(0, 2);
    int N;
    if (sizeType == 0) N = rnd.next(2, 5);
    else if (sizeType == 1) N = rnd.next(6, 10);
    else N = rnd.next(11, 15);

    // Choose difference K: small, medium, or large
    int kType = rnd.next(0, 2);
    int K;
    if (kType == 0) K = rnd.next(1, 5);
    else if (kType == 1) K = rnd.next(6, 20);
    else K = rnd.next(50, 100);

    // Upper bound for A_i to keep values hand-checkable
    int maxA = rnd.next(10, 100);

    // Generate A according to one of several patterns
    vector<int> A(N);
    int pattern = rnd.next(0, 4);
    if (pattern == 0) {
        // Fully random
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, maxA);
        }
    } else if (pattern == 1) {
        // Increasing-ish
        int incMax = max(1, maxA / N);
        A[0] = rnd.next(1, incMax);
        for (int i = 1; i < N; i++) {
            int d = rnd.next(0, K * 2);
            A[i] = A[i-1] + d;
            if (A[i] > maxA) A[i] = maxA - rnd.next(0, 2);
            if (A[i] < 1) A[i] = 1;
        }
    } else if (pattern == 2) {
        // Decreasing-ish
        int base = (N - 1) * K;
        int decStart = rnd.next(base + 1, base + maxA);
        A[0] = decStart;
        for (int i = 1; i < N; i++) {
            int d = rnd.next(0, K * 2);
            A[i] = A[i-1] - d;
            if (A[i] < 1) A[i] = rnd.next(1, maxA);
        }
    } else if (pattern == 3) {
        // Constant
        int c = rnd.next(1, maxA);
        for (int i = 0; i < N; i++) {
            A[i] = c;
        }
    } else {
        // Alternating low/high
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) A[i] = rnd.next(1, maxA / 2);
            else A[i] = rnd.next(maxA / 2 + 1, maxA);
        }
    }

    // Clamp to allowed bounds
    for (int &x : A) {
        if (x < 1) x = 1;
        else if (x > 100000) x = 100000;
    }

    // Output
    println(N, K);
    println(A);

    return 0;
}
