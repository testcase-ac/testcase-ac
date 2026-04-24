#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int N = rnd.next(2, 10);
    vector<int> H(N);

    // Hyperparameters for height distribution
    int mode = rnd.next(0, 3);
    int maxH = rnd.next(5, 20);

    if (mode == 0) {
        // Strictly increasing
        int cur = rnd.next(1, maxH / 2);
        for (int i = 0; i < N; i++) {
            cur += rnd.next(1, 5);
            H[i] = cur;
        }
    } else if (mode == 1) {
        // Fully random
        for (int i = 0; i < N; i++) {
            H[i] = rnd.next(1, maxH);
        }
    } else if (mode == 2) {
        // Values from a small distinct set
        int D = rnd.next(1, N);
        vector<int> vals(D);
        for (int i = 0; i < D; i++) {
            vals[i] = rnd.next(1, maxH);
        }
        for (int i = 0; i < N; i++) {
            H[i] = rnd.any(vals);
        }
    } else {
        // Mostly equal with a few spikes
        int base = rnd.next(1, maxH);
        for (int i = 0; i < N; i++) {
            H[i] = base;
        }
        int spikes = rnd.next(1, N - 1);
        for (int i = 0; i < spikes; i++) {
            int idx = rnd.next(0, N - 1);
            H[idx] = base + rnd.next(1, maxH);
        }
    }

    // Randomize input order
    shuffle(H.begin(), H.end());

    // Output
    println(N);
    println(H);

    return 0;
}
