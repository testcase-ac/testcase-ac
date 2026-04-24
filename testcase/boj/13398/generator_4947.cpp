#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checking
    int n = rnd.next(1, 10);

    // Hyper-parameter: distribution of magnitudes
    // 0 = uniform [0,1000]
    // 1 = bias small (min of 2 samples)
    // 2 = bias large (max of 2 samples)
    int modeMag = rnd.next(0, 2);

    // Hyper-parameter: probability of negative values
    double negProb = rnd.next();

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int mag;
        if (modeMag == 0) {
            mag = rnd.next(0, 1000);
        } else if (modeMag == 1) {
            mag = rnd.wnext(1001, -1); // min of 2 => small
        } else {
            mag = rnd.wnext(1001, 1);  // max of 2 => large
        }
        bool isNeg = rnd.next() < negProb;
        a[i] = isNeg ? -mag : mag;
    }

    // Ensure at least one non-zero element
    bool allZero = true;
    for (int v : a) if (v != 0) { allZero = false; break; }
    if (allZero) {
        int idx = rnd.next(0, n-1);
        int mag = rnd.next(1, 1000);
        a[idx] = rnd.next(0,1) ? mag : -mag;
    }

    // Output
    println(n);
    println(a);

    return 0;
}
