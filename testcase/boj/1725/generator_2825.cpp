#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of bars
    int N = rnd.next(1, 10);
    vector<long long> h(N);
    // Maximum base height
    int maxH = rnd.next(1, 20);
    // Choose a pattern for diversity
    int pattern = rnd.next(0, 5);
    int den = max(1, N - 1);
    switch (pattern) {
    case 0:
        // Pure random
        for (int i = 0; i < N; i++) {
            h[i] = rnd.next(0, maxH);
        }
        break;
    case 1: {
        // Increasing with noise
        int base = rnd.next(0, maxH / 2);
        int maxDelta = max(1, maxH / den);
        int delta = rnd.next(1, maxDelta);
        for (int i = 0; i < N; i++) {
            h[i] = base + delta * i + rnd.next(0, delta);
        }
        break;
    }
    case 2: {
        // Decreasing with noise
        int base = rnd.next(0, maxH / 2);
        int maxDelta = max(1, maxH / den);
        int delta = rnd.next(1, maxDelta);
        for (int i = 0; i < N; i++) {
            h[i] = base + delta * (N - 1 - i) + rnd.next(0, delta);
        }
        break;
    }
    case 3: {
        // Valley shape
        int m = rnd.next(0, N - 1);
        int maxK = max(1, maxH / den);
        int k = rnd.next(1, maxK);
        for (int i = 0; i < N; i++) {
            int d = i - m;
            if (d < 0) d = -d;
            h[i] = 1LL * d * k;
        }
        break;
    }
    case 4: {
        // Mountain shape
        int m = rnd.next(0, N - 1);
        int maxK = max(1, maxH / den);
        int k = rnd.next(1, maxK);
        int maxDist = max(m, N - 1 - m);
        int lo = min(1LL * k * maxDist, (long long)maxH);
        int peak = rnd.next(lo, maxH);
        for (int i = 0; i < N; i++) {
            int d = i - m;
            if (d < 0) d = -d;
            long long val = peak - 1LL * k * d;
            h[i] = val > 0 ? val : 0;
        }
        break;
    }
    case 5: {
        // Single block
        int s = rnd.next(1, N);
        int p = rnd.next(0, N - s);
        int blockH = rnd.next(maxH / 2, maxH);
        for (int i = 0; i < N; i++) {
            if (i >= p && i < p + s)
                h[i] = blockH;
            else
                h[i] = rnd.next(0, maxH / 2);
        }
        break;
    }
    }
    // Occasionally insert an extreme high bar
    if (rnd.next(0, 4) == 0 && N > 0) {
        int idx = rnd.next(0, N - 1);
        h[idx] = maxH + rnd.next(1, 20);
    }
    // Output
    println(N);
    for (auto x : h) println(x);
    return 0;
}
