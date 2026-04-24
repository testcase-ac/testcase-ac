#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size
    int N = rnd.next(1, 10);

    // Prepare a sorted sequence
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
    }

    // Hyper-parameter: type of permutation
    // 0 = fully random, 1 = almost sorted, 2 = reversed + some noise
    int t = rnd.next(0, 2);

    if (t == 0) {
        // fully random
        shuffle(a.begin(), a.end());
    } else if (t == 1) {
        // almost sorted: make small adjacent swaps
        for (int i = 0; i + 1 < N; i++) {
            // 20% chance to swap each adjacent pair
            if (rnd.next(0, 9) < 2) {
                swap(a[i], a[i+1]);
            }
        }
    } else {
        // reversed + a few random swaps
        reverse(a.begin(), a.end());
        int k = rnd.next(0, N/2);
        for (int i = 0; i < k; i++) {
            int x = rnd.next(0, N-1);
            int y = rnd.next(0, N-1);
            swap(a[x], a[y]);
        }
    }

    // Output in required format
    println(N);
    println(a);

    return 0;
}
