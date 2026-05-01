#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of files
    int N = rnd.next(1, 15);

    // Number of clusters to induce groups of similar sizes
    int C = rnd.next(1, min(N, 5));

    // Generate cluster pivots
    vector<int> pivot(C);
    for (int i = 0; i < C; i++) {
        // Base size between 1 and 1000
        pivot[i] = rnd.next(1, 1000);
    }

    // Assign sizes with variation: exact, near-threshold, far
    vector<int> sizes;
    sizes.reserve(N);
    for (int i = 0; i < N; i++) {
        int ci = rnd.next(0, C - 1);
        double p = rnd.next();
        double delta;
        if (p < 0.20) {
            // exactly the pivot
            delta = 0.0;
        } else if (p < 0.60) {
            // small variation within ±10%
            delta = rnd.next(-10, 10) / 100.0;
        } else {
            // larger variation outside ±10%
            double mag = rnd.next(11, 99) / 100.0;
            // sometimes even larger positive
            if (rnd.next() < 0.3) {
                mag = rnd.next(11, 500) / 100.0;
            }
            delta = (rnd.next() < 0.5 ? mag : -mag);
        }
        double val = pivot[ci] * (1.0 + delta);
        int s = max(1, int(val + 0.5));
        sizes.push_back(s);
    }

    // Shuffle to hide cluster order
    shuffle(sizes.begin(), sizes.end());

    // Output the test case
    println(N);
    println(sizes);

    return 0;
}
