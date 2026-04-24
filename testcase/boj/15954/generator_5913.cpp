#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Choose N biased towards small, medium, large
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.3) {
        N = rnd.next(2, 3);
    } else if (p < 0.6) {
        N = rnd.next(4, 10);
    } else if (p < 0.9) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 50);
    }

    // 2) K in [1, N]
    int K = rnd.next(1, N);

    // 3) Choose an upper bound maxA for the values
    double q = rnd.next();
    int maxA;
    if (q < 0.5) {
        maxA = rnd.next(0, 10);
    } else if (q < 0.8) {
        maxA = rnd.next(11, 1000);
    } else if (q < 0.95) {
        maxA = rnd.next(1001, 100000);
    } else {
        maxA = rnd.next(100001, 1000000);
    }

    // 4) Prepare the array under different styles for variability
    int style = rnd.next(0, 6);
    vector<int> a(N);
    switch (style) {
        case 0: // Fully random
            for (int i = 0; i < N; i++) {
                a[i] = rnd.next(0, maxA);
            }
            break;
        case 1: { // Strictly increasing
            int curr = rnd.next(0, maxA);
            int stepMax = max(1, maxA / max(1, N) + 1);
            for (int i = 0; i < N; i++) {
                a[i] = curr;
                curr += rnd.next(0, stepMax);
                if (curr > maxA) curr = maxA;
            }
            break;
        }
        case 2: { // Strictly decreasing
            int curr = rnd.next(0, maxA);
            int stepMax = max(1, maxA / max(1, N) + 1);
            for (int i = 0; i < N; i++) {
                a[i] = curr;
                curr -= rnd.next(0, stepMax);
                if (curr < 0) curr = 0;
            }
            break;
        }
        case 3: // Two clusters
            if (N >= 2) {
                int b = rnd.next(1, N - 1);
                int mid = maxA / 2;
                for (int i = 0; i < b; i++) a[i] = rnd.next(0, mid);
                for (int i = b; i < N; i++) a[i] = rnd.next(mid, maxA);
            } else {
                for (int i = 0; i < N; i++) a[i] = rnd.next(0, maxA);
            }
            break;
        case 4: { // Sawtooth pattern
            int period = rnd.next(1, N);
            for (int i = 0; i < N; i++) {
                a[i] = i % period;
            }
            break;
        }
        case 5: { // Constant array
            int v = rnd.next(0, maxA);
            fill(a.begin(), a.end(), v);
            break;
        }
        case 6: { // One outlier among equals
            vector<int> opts1 = {0, maxA / 2, maxA};
            int base = rnd.any(opts1);
            for (int i = 0; i < N; i++) a[i] = base;
            int idx = rnd.next(0, N - 1);
            vector<int> opts2 = {0, maxA};
            a[idx] = rnd.any(opts2);
            break;
        }
    }

    // 5) Shuffle only in the truly random or one‐outlier cases
    if (style == 0 || style == 6) {
        shuffle(a.begin(), a.end());
    }

    // Output
    println(N, K);
    println(a);

    return 0;
}
