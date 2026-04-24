#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of multi-taps
    int N = rnd.next(1, 10);

    // A rough upper bound for plug counts
    int ai_max = rnd.next(1, 1000);

    // Generate diverse sizes: some very small, some skewed, some uniform
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        if (p < 0.3) {
            // very small plugs
            a[i] = rnd.next(1, 3);
        } else if (p < 0.6) {
            // skewed towards larger values
            a[i] = rnd.wnext(max(1, ai_max), 3);
        } else {
            // uniform in [1, ai_max]
            a[i] = rnd.next(1, max(1, ai_max));
        }
    }

    // Shuffle order to avoid any sorted patterns
    shuffle(a.begin(), a.end());

    // Output
    println(N);
    for (int x : a) println(x);

    return 0;
}
