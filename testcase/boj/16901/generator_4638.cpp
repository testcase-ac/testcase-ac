#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(1, 10);
    // Hyper-parameter: bit-width for values
    int B = rnd.next(1, 5);
    int MAX = (1 << B) - 1;

    // Decide if we produce clustered values
    bool cluster = rnd.next() < 0.5;
    // Decide if we introduce duplicates
    bool clones = rnd.next() < 0.5;

    vector<int> A(N);
    if (!cluster) {
        // Uniform random values
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(0, MAX);
        }
    } else {
        // Two clusters: [0..mid] and [mid..MAX]
        int mid = rnd.next(0, MAX);
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.5)
                A[i] = rnd.next(0, mid);
            else
                A[i] = rnd.next(mid, MAX);
        }
    }

    if (clones && N >= 2) {
        // Introduce some duplicates by cloning earlier values
        int c = rnd.next(1, N - 1);
        for (int k = 0; k < c; k++) {
            int idx = rnd.next(1, N - 1);
            int from = rnd.next(0, idx - 1);
            A[idx] = A[from];
        }
    }

    // Shuffle to avoid any ordering pattern
    shuffle(A.begin(), A.end());

    // Output
    println(N);
    println(A);

    return 0;
}
