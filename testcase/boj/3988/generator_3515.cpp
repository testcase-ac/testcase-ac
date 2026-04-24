#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N and valid K
    int N = rnd.next(3, 10);
    int K = rnd.next(1, N - 2);

    // Hyper-parameter: limit for absolute values
    int rangeLim = rnd.next(10, 50);

    // Decide whether to use uniform or clustered distribution
    bool uniformDist = rnd.next(0, 1) == 0;
    vector<int> V(N);

    if (uniformDist) {
        // Uniform integers in [-rangeLim, rangeLim]
        for (int i = 0; i < N; i++) {
            V[i] = rnd.next(-rangeLim, rangeLim);
        }
    } else {
        // Clustered around random centers
        int C = rnd.next(1, min(N, 3));
        vector<int> centers(C);
        for (int i = 0; i < C; i++) {
            centers[i] = rnd.next(-rangeLim, rangeLim);
        }
        int spread = rnd.next(0, rangeLim);
        for (int i = 0; i < N; i++) {
            int c = rnd.next(0, C - 1);
            V[i] = centers[c] + rnd.next(-spread, spread);
        }
    }

    // Randomly introduce duplicates
    double dupProb = rnd.next();
    shuffle(V.begin(), V.end());
    for (int i = 1; i < N; i++) {
        if (rnd.next() < dupProb) {
            V[i] = V[rnd.next(0, i - 1)];
        }
    }

    // Final random shuffle
    shuffle(V.begin(), V.end());

    // Output
    println(N, K);
    println(V);

    return 0;
}
