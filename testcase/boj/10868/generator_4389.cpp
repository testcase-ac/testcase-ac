#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Generate array values with diverse patterns
    vector<int> a(N);
    int valType = rnd.next(0, 2);
    if (valType == 0) {
        // Uniform in a random small range
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, lo + rnd.next(0, 900));
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (valType == 1) {
        // Few distinct values
        int K = rnd.next(1, N);
        vector<int> distinct(K);
        for (int i = 0; i < K; i++) {
            distinct[i] = rnd.next(1, 1000);
        }
        for (int i = 0; i < N; i++) {
            a[i] = rnd.any(distinct);
        }
    } else {
        // Monotonic sequence (increasing or decreasing)
        bool inc = rnd.next(0, 1);
        int start = rnd.next(1, 1000);
        for (int i = 0; i < N; i++) {
            int step = rnd.next(0, 5);
            a[i] = start + i * step;
        }
        if (!inc) {
            reverse(a.begin(), a.end());
        }
    }

    // Output N, M
    println(N, M);
    // Output the array
    for (int x : a) {
        println(x);
    }

    // Generate queries with varied range lengths
    for (int i = 0; i < M; i++) {
        int qType = rnd.next(0, 3);
        int l, r;
        if (qType == 0) {
            // Single-element queries
            l = rnd.next(1, N);
            r = l;
        } else if (qType == 1) {
            // Full-range query
            l = 1;
            r = N;
        } else if (qType == 2) {
            // Very small range (length up to 3)
            l = rnd.next(1, N);
            r = min(N, l + rnd.next(0, 2));
        } else {
            // Random valid range
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        println(l, r);
    }

    return 0;
}
