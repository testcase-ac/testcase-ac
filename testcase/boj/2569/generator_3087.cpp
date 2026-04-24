#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of containers
    int N = rnd.next(1, 10);

    // Decide a value range [low, high] with enough room for N distinct weights
    int low = rnd.next(1, 20);
    int high = rnd.next(low + N - 1, low + 100);

    // Build a pool of all possible weights in [low, high]
    vector<int> pool(high - low + 1);
    iota(pool.begin(), pool.end(), low);
    shuffle(pool.begin(), pool.end());

    // Pick first N and sort to get the distinct weights
    pool.resize(N);
    sort(pool.begin(), pool.end());
    vector<int> weights = pool;

    // Create different permutation modes for diversity
    int modeMax = (N == 1 ? 0 : 2);
    int mode = rnd.next(0, modeMax);

    // Generate the initial arrangement
    vector<int> perm = weights;
    if (mode == 0) {
        // Fully random permutation
        shuffle(perm.begin(), perm.end());
    } else if (mode == 1) {
        // Completely reversed
        reverse(perm.begin(), perm.end());
    } else {
        // Near-sorted: a few adjacent swaps
        int swaps = rnd.next(1, N / 2);
        for (int i = 0; i < swaps; i++) {
            int idx = rnd.next(0, N - 2);
            swap(perm[idx], perm[idx + 1]);
        }
    }

    // Output the test case
    println(N);
    for (int x : perm) {
        println(x);
    }

    return 0;
}
