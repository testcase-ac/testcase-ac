#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of houses
    int N = rnd.next(1, 10);
    // Maximum coordinate value
    int C = rnd.next(1, 20);

    // Sampling mode: 0 = uniform, 1 = skew low, 2 = skew high
    int mode = rnd.next(0, 2);
    // Probability to reuse an existing coordinate (to create duplicates)
    double dupProb = rnd.next(0.0, 1.0);

    vector<int> pos;
    pos.reserve(N);
    for (int i = 0; i < N; i++) {
        int x;
        // Decide whether to duplicate
        if (i > 0 && rnd.next() < dupProb) {
            x = rnd.any(pos);
        } else {
            // Generate according to mode
            if (mode == 0) {
                x = rnd.next(1, C);
            } else if (mode == 1) {
                // skew to low values
                x = rnd.wnext(C, -1) + 1;
            } else {
                // skew to high values
                x = rnd.wnext(C, +1) + 1;
            }
        }
        pos.push_back(x);
    }

    // Shuffle order to avoid sorted inputs
    shuffle(pos.begin(), pos.end());

    // Output
    println(N);
    println(pos);

    return 0;
}
