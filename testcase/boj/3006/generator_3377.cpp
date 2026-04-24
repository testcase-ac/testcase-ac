#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkability
    int N = rnd.next(1, 10);

    // Base permutation: sorted 1..N
    vector<int> a(N);
    for (int i = 0; i < N; i++) a[i] = i + 1;

    // Choose a pattern type for diversity
    // If N < 3, limit to random or sorted
    int tp = (N >= 3 ? rnd.next(0, 4) : rnd.next(0, 1));

    if (tp == 0) {
        // Fully random permutation
        shuffle(a.begin(), a.end());
    } else if (tp == 1) {
        // Already sorted ascending; do nothing
    } else if (tp == 2) {
        // Fully reversed
        reverse(a.begin(), a.end());
    } else if (tp == 3) {
        // Nearly sorted: apply a few random swaps
        int swaps = rnd.next(1, min(N, 3));
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, N - 1);
            int y = rnd.next(0, N - 1);
            swap(a[x], a[y]);
        }
    } else if (tp == 4) {
        // Single block reversal inside the sorted array
        int l = rnd.next(0, N - 2);
        int r = rnd.next(l + 1, N - 1);
        reverse(a.begin() + l, a.begin() + r + 1);
    }

    // Output in the required format
    println(N);
    for (int x : a) {
        println(x);
    }

    return 0;
}
