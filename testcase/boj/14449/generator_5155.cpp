#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small size for hand-checkable
    int N = rnd.next(2, 10);

    // decide pattern type for diversity
    int pattern = rnd.next(1, 6);

    // base sequence 1..N
    vector<int> a(N);
    iota(a.begin(), a.end(), 1);

    if (pattern == 1) {
        // fully random
        shuffle(a.begin(), a.end());
    } else if (pattern == 2) {
        // sorted increasing (1..N)
        // nothing to do
    } else if (pattern == 3) {
        // sorted decreasing
        reverse(a.begin(), a.end());
    } else if (pattern == 4) {
        // mostly sorted but swap two random positions
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        while (j == i) j = rnd.next(0, N - 1);
        swap(a[i], a[j]);
    } else if (pattern == 5) {
        // first half increasing, second half decreasing
        vector<int> b;
        int half = N / 2;
        for (int i = 1; i <= half; i++) b.push_back(i);
        for (int i = N; i > half; i--) b.push_back(i);
        a = b;
    } else {
        // sorted with a few adjacent swaps
        int swaps = rnd.next(1, max(1, N/2));
        for (int t = 0; t < swaps; t++) {
            int idx = rnd.next(0, N - 2);
            swap(a[idx], a[idx+1]);
        }
    }

    // output
    println(N);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }

    return 0;
}
