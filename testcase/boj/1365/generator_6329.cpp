#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for N: biased small or large within [1,20]
    int t_choice = rnd.any(vector<int>{-3, -2, -1, 1, 2, 3});
    int N = rnd.wnext(20, t_choice) + 1;

    // Build initial sorted permutation 1..N
    vector<int> p(N);
    iota(p.begin(), p.end(), 1);

    // Choose a pattern to generate diverse cases
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // fully random permutation
        shuffle(p.begin(), p.end());
    } else if (pattern == 1) {
        // already sorted
    } else if (pattern == 2) {
        // fully reversed
        reverse(p.begin(), p.end());
    } else {
        // almost sorted: small number of random swaps
        int swaps = rnd.next(1, max(1, N / 4));
        for (int i = 0; i < swaps; i++) {
            int a = rnd.next(0, N - 1);
            int b = rnd.next(0, N - 1);
            swap(p[a], p[b]);
        }
    }

    // Output
    println(N);
    println(p);

    return 0;
}
