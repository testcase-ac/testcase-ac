#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small n for hand-checkable cases
    int n = rnd.next(1, 10);

    // Hyper-parameter: choose coordinate upper bound
    int highBound = rnd.next(0, 1) ? 1000000000 : 1000;

    // Hyper-parameter: distribution type
    // 0 = uniform random, 1 = arithmetic progression, 2 = many duplicates
    int dtype = rnd.next(0, 2);

    vector<int> x(n);
    if (dtype == 0) {
        // Uniform random values in [0, highBound]
        for (int i = 0; i < n; i++) {
            x[i] = rnd.next(0, highBound);
        }
    } else if (dtype == 1) {
        // Arithmetic progression within [0, highBound]
        int start = rnd.next(0, highBound);
        int maxstep = (n > 1 ? (highBound - start) / (n - 1) : 0);
        int step = rnd.next(0, maxstep);
        for (int i = 0; i < n; i++) {
            x[i] = start + i * step;
        }
    } else {
        // Many duplicates: pick a small pool of unique values
        int uniq = rnd.next(1, max(1, n / 3));
        vector<int> pool(uniq);
        for (int i = 0; i < uniq; i++) {
            pool[i] = rnd.next(0, highBound);
        }
        for (int i = 0; i < n; i++) {
            x[i] = rnd.any(pool);
        }
    }

    // Shuffle to avoid giving sorted input
    shuffle(x.begin(), x.end());

    // Output format
    println(n);
    println(x);

    return 0;
}
