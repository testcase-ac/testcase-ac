#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose n in small, medium, large ranges for variability (2 <= n <= 30)
    int sizeCategory = rnd.next(0, 2);
    int n;
    if (sizeCategory == 0) {
        n = rnd.next(2, 5);
    } else if (sizeCategory == 1) {
        n = rnd.next(6, 15);
    } else {
        n = rnd.next(16, 30);
    }
    int k = rnd.next(1, min(n - 1, 10));
    int total = 3 * n;
    vector<int> a(total);

    // Choose distribution type for temperatures
    int distType = rnd.next(0, 3);
    if (distType == 0) {
        // Uniform random in [lo, hi]
        int lo = rnd.next(1, 500000);
        int hi = rnd.next(lo, 1000000);
        for (int i = 0; i < total; i++) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (distType == 1) {
        // Mountain shape: increase to a peak then decrease
        int peakPos = rnd.next(1, total - 2);
        int peakVal = rnd.next(1, 1000000);
        for (int i = 0; i <= peakPos; i++) {
            int v = (int)((long long)peakVal * i / peakPos);
            a[i] = max(1, v);
        }
        for (int i = peakPos + 1; i < total; i++) {
            int v = (int)((long long)peakVal * (total - 1 - i) / (total - 1 - peakPos));
            a[i] = max(1, v);
        }
    } else if (distType == 2) {
        // Random blocks of constant temperature
        int blocks = rnd.next(1, n);
        vector<int> sizes(blocks);
        int rem = total;
        for (int i = 0; i < blocks; i++) {
            if (i + 1 == blocks) {
                sizes[i] = rem;
            } else {
                int mx = rem - (blocks - i - 1);
                sizes[i] = rnd.next(1, mx);
                rem -= sizes[i];
            }
        }
        int idx = 0;
        for (int b = 0; b < blocks; b++) {
            int val = rnd.next(1, 1000000);
            for (int j = 0; j < sizes[b]; j++) {
                a[idx++] = val;
            }
        }
    } else {
        // Low base with few high peaks
        for (int i = 0; i < total; i++) {
            a[i] = rnd.next(1, 100000);
        }
        int peaks = rnd.next(1, min(total, 10));
        for (int i = 0; i < peaks; i++) {
            int pos = rnd.next(0, total - 1);
            a[pos] = rnd.next(500001, 1000000);
        }
    }

    // Optionally shuffle some distributions to avoid order biases
    if (distType != 1 && rnd.next(0, 1) == 0) {
        shuffle(a.begin(), a.end());
    }

    // Output the test case
    println(n, k);
    println(a);
    return 0;
}
