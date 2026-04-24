#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Ensure N >= 2 to avoid invalid ranges
    int N = rnd.next(2, 10);

    // Generate left side permutation with structural variation
    vector<int> left(N);
    iota(left.begin(), left.end(), 1);
    int typeL = rnd.next(0, 3);
    if (typeL == 0) {
        // completely random
        shuffle(left.begin(), left.end());
    } else if (typeL == 2) {
        // reversed
        reverse(left.begin(), left.end());
    } else if (typeL == 3) {
        // a few random adjacent swaps
        int swaps = rnd.next(1, N/2);
        for (int i = 0; i < swaps; i++) {
            int pos = rnd.next(0, N - 2);
            swap(left[pos], left[pos + 1]);
        }
    }
    // typeL == 1: sorted, do nothing

    // Generate right side, sometimes correlated to left
    vector<int> right;
    bool correlated = rnd.next(0, 1) == 1;
    if (correlated) {
        right = left;
        // Apply a few adjacent swaps to create near-correlation
        int swaps = rnd.next(1, N/2);
        for (int i = 0; i < swaps; i++) {
            int pos = rnd.next(0, N - 2);
            swap(right[pos], right[pos + 1]);
        }
    } else {
        right.resize(N);
        iota(right.begin(), right.end(), 1);
        int typeR = rnd.next(0, 3);
        if (typeR == 0) {
            shuffle(right.begin(), right.end());
        } else if (typeR == 2) {
            reverse(right.begin(), right.end());
        } else if (typeR == 3) {
            int swaps = rnd.next(1, N/2);
            for (int i = 0; i < swaps; i++) {
                int pos = rnd.next(0, N - 2);
                swap(right[pos], right[pos + 1]);
            }
        }
        // typeR == 1: sorted, do nothing
    }

    // Output in the required format
    println(N);
    for (int x : left) println(x);
    for (int x : right) println(x);
    return 0;
}
