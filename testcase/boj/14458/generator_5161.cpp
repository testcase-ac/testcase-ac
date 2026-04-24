#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 2 and 10
    int N = rnd.next(2, 10);

    // Prepare containers
    vector<int> L(N), R(N);
    for (int i = 0; i < N; i++) {
        L[i] = i + 1;
        R[i] = i + 1;
    }

    // Hyper-parameter: choose a pattern type
    int tp = rnd.next(0, 4);
    if (tp == 0) {
        // both random permutations
        shuffle(L.begin(), L.end());
        shuffle(R.begin(), R.end());
    } else if (tp == 1) {
        // both identity (1,2,...,N)
        // L and R already set
    } else if (tp == 2) {
        // left identity, right reversed
        for (int i = 0; i < N; i++) {
            R[i] = N - i;
        }
    } else if (tp == 3) {
        // left random, right is left with a few random swaps
        shuffle(L.begin(), L.end());
        R = L;
        int swaps = rnd.next(1, 3);
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, N - 1);
            int y = rnd.next(0, N - 1);
            swap(R[x], R[y]);
        }
    } else {
        // tp == 4: left random, right is a single rotation of left
        shuffle(L.begin(), L.end());
        int k = rnd.next(1, N - 1);
        for (int i = 0; i < N; i++) {
            R[i] = L[(i + k) % N];
        }
    }

    // Output in required format
    println(N);
    for (int i = 0; i < N; i++) {
        println(L[i]);
    }
    for (int i = 0; i < N; i++) {
        println(R[i]);
    }

    return 0;
}
