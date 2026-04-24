#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N, M for manual check
    int N = rnd.next(1, 15);
    int M = rnd.next(1, 15);

    // Output N and M
    println(N, M);

    // Generate the array with diverse distributions
    vector<int> a(N);
    int dtype = rnd.next(0, 2);
    if (dtype == 0) {
        // Uniform over full range
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 1000000000);
    } else if (dtype == 1) {
        // Small values only
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 100);
    } else {
        // Monotonic with occasional flips
        bool inc = rnd.next() < 0.5;
        a[0] = rnd.next(1, 1000000000);
        for (int i = 1; i < N; i++) {
            int delta = rnd.next(0, 1000);
            if (inc)
                a[i] = min(1000000000, a[i-1] + delta);
            else
                a[i] = max(1, a[i-1] - delta);
            if (rnd.next() < 0.2) inc = !inc;
        }
    }
    // Print the array
    for (int i = 0; i < N; i++)
        println(a[i]);

    // Generate M queries with varied lengths
    for (int i = 0; i < M; i++) {
        double p = rnd.next();
        int l, r;
        if (p < 0.2) {
            // Single-point query
            l = r = rnd.next(1, N);
        } else if (p < 0.4 && N >= 3) {
            // Small range of length 2-3
            int len = rnd.next(2, min(3, N));
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else if (p < 0.6 && N >= 5) {
            // Medium range length 4 to min(10, N)
            int len = rnd.next(4, min(N, 10));
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else if (p < 0.8 && N >= 2) {
            // Large range length close to N
            int minL = max(2, N - 3);
            int len = rnd.next(minL, N);
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else {
            // Full-range query
            l = 1;
            r = N;
        }
        println(l, r);
    }
    return 0;
}
