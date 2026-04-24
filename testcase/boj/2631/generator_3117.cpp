#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for size diversity
    int N = rnd.next(2, 10);

    // Prepare a sorted sequence 1..N
    vector<int> a(N);
    for (int i = 0; i < N; i++) a[i] = i + 1;

    // Choose a noise type to create diverse permutations
    int noiseType = rnd.next(0, 4);
    if (noiseType == 0) {
        // Completely random permutation
        shuffle(a.begin(), a.end());
    }
    else if (noiseType == 1) {
        // Almost sorted: apply a few random adjacent swaps
        int k = rnd.next(1, max(1, N/2));
        for (int i = 0; i < k; i++) {
            int pos = rnd.next(0, N - 2);
            swap(a[pos], a[pos + 1]);
        }
    }
    else if (noiseType == 2) {
        // Reversed sequence
        reverse(a.begin(), a.end());
    }
    else if (noiseType == 3) {
        // Few random moves: pick an element and move it to another position
        int k = rnd.next(1, max(1, N/3));
        for (int t = 0; t < k; t++) {
            int x = rnd.next(0, N - 1);
            int y;
            do {
                y = rnd.next(0, N - 1);
            } while (y == x);
            int v = a[x];
            a.erase(a.begin() + x);
            // adjust y if needed after erase
            if (y > x) y--;
            a.insert(a.begin() + y, v);
        }
    }
    // noiseType == 4: leave it fully sorted

    // Output in required format
    println(N);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    return 0;
}
