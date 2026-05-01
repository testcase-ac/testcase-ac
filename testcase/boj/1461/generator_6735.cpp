#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of books
    int N = rnd.next(1, 50);
    // Carry capacity biased towards extremes or middle
    vector<int> ts = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(ts);
    int M = rnd.wnext(N, t);
    if (M < 1) M = 1;

    // Probability of far books
    double farProb = rnd.next(0.0, 1.0);
    vector<int> pos(N);
    for (int i = 0; i < N; i++) {
        int d;
        if (rnd.next() < farProb) {
            d = rnd.next(5000, 10000);
        } else {
            d = rnd.next(1, 200);
        }
        int sign = (rnd.next() < 0.5 ? -1 : 1);
        pos[i] = sign * d;
    }

    // Ensure at least one positive and one negative if possible
    if (N >= 2) {
        bool hasPos = false, hasNeg = false;
        for (int x : pos) {
            if (x > 0) hasPos = true;
            if (x < 0) hasNeg = true;
        }
        if (!hasPos) {
            int idx = rnd.next(0, N - 1);
            pos[idx] = abs(pos[idx]);
        }
        if (!hasNeg) {
            int idx = rnd.next(0, N - 1);
            pos[idx] = -abs(pos[idx]);
        }
    }

    shuffle(pos.begin(), pos.end());

    // Output
    println(N, M);
    println(pos);

    return 0;
}
