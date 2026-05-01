#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: biased small or large
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(12, tN) + 1;  // yields [1..12], biased by tN

    // Generate strictly increasing positions X
    vector<int> X(N);
    int base_max = rnd.wnext(100, rnd.next(-1, 1));
    int hi0 = max(1, base_max);
    X[0] = rnd.next(1, hi0);
    for (int i = 1; i < N; ++i) {
        int diff;
        if (rnd.next() < 0.7) {
            diff = rnd.next(1, 10);
        } else {
            int hi_diff = rnd.wnext(1000, rnd.next(-1, 1));
            hi_diff = max(20, hi_diff);
            diff = rnd.next(20, hi_diff);
        }
        X[i] = X[i-1] + diff;
    }

    // Generate times T with several modes
    int mode = rnd.next(0, 3);
    int tmax = rnd.wnext(10000000, rnd.next(-1, 1));
    vector<int> T(N);
    if (mode == 0) {
        // all zero times
        for (int i = 0; i < N; ++i) T[i] = 0;
    } else {
        // random times then optionally sort
        for (int i = 0; i < N; ++i) {
            T[i] = rnd.next(0, tmax);
        }
        if (mode == 1) {
            sort(T.begin(), T.end());
        } else if (mode == 2) {
            sort(T.begin(), T.end(), greater<int>());
        }
        // mode==3: keep random
    }

    // Output
    println(N);
    println(X);
    println(T);
    return 0;
}
