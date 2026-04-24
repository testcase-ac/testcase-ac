#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for total time T
    int T = rnd.next(1, 20);
    // Hyper-parameter for maximum moves W
    int W;
    if (rnd.next(2) == 0) {
        // sometimes bound by T
        W = rnd.next(1, min(30, T));
    } else {
        // sometimes larger than T (still valid since W ≤ 30)
        W = rnd.next(1, 30);
    }

    // Generate the falling sequence with two modes
    vector<int> a(T);
    if (rnd.next(2) == 0) {
        // Mode 1: independent uniform random drops
        for (int i = 0; i < T; i++) {
            a[i] = rnd.next(1, 2);
        }
    } else {
        // Mode 2: run-based drops with random run lengths
        int curr = rnd.next(1, 2);
        int rem = T, idx = 0;
        // bias parameter for run lengths
        int runBias = rnd.next(-2, 2);
        while (rem > 0) {
            // generate a run length L in [1..rem]
            int L = rnd.wnext(rem, runBias) + 1;
            for (int j = 0; j < L; j++) {
                a[idx++] = curr;
            }
            rem -= L;
            curr = 3 - curr; // switch between 1 and 2
        }
    }

    // Output
    println(T, W);
    for (int x : a) {
        println(x);
    }
    return 0;
}
