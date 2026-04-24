#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of stacks
    int n = rnd.next(1, 10);
    vector<long long> a(n);

    // Choose a pattern for diversity
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Uniform heights
        long long v = rnd.next(0, 20);
        for (int i = 0; i < n; i++) {
            a[i] = v;
        }
    } else if (pattern == 1) {
        // Ramp pattern
        long long start = rnd.next(0, 5);
        for (int i = 0; i < n; i++) {
            a[i] = start + i;
        }
    } else {
        // Fully random pattern
        long long Hmax = rnd.next(0, 20);
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(0LL, Hmax);
        }
    }

    // Ensure total containers ≥ 1
    long long sum = 0;
    for (auto x : a) sum += x;
    if (sum == 0) {
        int idx = rnd.next(0, n - 1);
        a[idx] = rnd.next(1, 20);
    }

    // Shuffle to avoid sorted patterns
    shuffle(a.begin(), a.end());

    // Output
    println(n);
    println(a);

    return 0;
}
