#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter ranges
    const int MAX_L = 20;
    const int MAX_W = 20;
    const int MAX_N = 50;

    // Generate garden dimensions with bias towards small or large
    int l, w;
    if (rnd.next(0, 1) == 0) {
        // bias towards smaller l
        l = rnd.wnext(MAX_L, -1) + 1;  // minimum of two samples in [1..MAX_L]
    } else {
        // bias towards larger l
        l = rnd.wnext(MAX_L, 1) + 1;   // maximum of two samples in [1..MAX_L]
    }
    if (rnd.next(0, 1) == 0) {
        w = rnd.wnext(MAX_W, -1) + 1;
    } else {
        w = rnd.wnext(MAX_W, 1) + 1;
    }

    // Sometimes swap to get thin shapes
    if (rnd.next(0,1) == 0) {
        swap(l, w);
    }

    // Number of roses: up to twice the number of cells, capped
    int cellCount = l * w;
    int maxRoses = min(cellCount * 2, MAX_N);
    int n = rnd.next(2, maxRoses);

    // Each gardener gets k roses: 1 <= k <= n/2
    int k = rnd.next(1, n/2);

    // Output first two lines
    println(l, w);
    println(n, k);

    // Generate rose positions (duplicates allowed)
    for (int i = 0; i < n; i++) {
        int x = rnd.next(1, l);
        int y = rnd.next(1, w);
        println(x, y);
    }

    return 0;
}
