#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size N for hand-checkable tests
    int N = rnd.next(1, 10);

    // Choose a max height at least N up to a bit larger for diversity
    int maxH = max(N, rnd.next(N, 20));

    // Generate a pool of distinct heights 1..maxH and sample N of them
    vector<int> pool(maxH);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    vector<int> sample(pool.begin(), pool.begin() + N);
    sort(sample.begin(), sample.end());

    // Decide on a pattern type for diversity
    // 0: increasing, 1: decreasing, 2: random, 3: zigzag
    int pattern = rnd.next(0, 3);
    vector<int> heights(N);
    if (pattern == 0) {
        // strictly increasing
        heights = sample;
    } else if (pattern == 1) {
        // strictly decreasing
        heights = sample;
        reverse(heights.begin(), heights.end());
    } else if (pattern == 2) {
        // fully random permutation
        heights = sample;
        shuffle(heights.begin(), heights.end());
    } else {
        // zigzag: high, low, 2nd high, 2nd low, ...
        int l = 0, r = N - 1;
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) {
                heights[i] = sample[r--];
            } else {
                heights[i] = sample[l++];
            }
        }
    }

    // Output the test case
    println(N);
    println(heights);

    return 0;
}
