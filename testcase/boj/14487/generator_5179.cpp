#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of towns
    double p = rnd.next();
    int n;
    if (p < 0.3) n = rnd.next(1, 3);
    else if (p < 0.7) n = rnd.next(4, 7);
    else n = rnd.next(8, 10);

    // Hyper-parameter for maximum weight
    int Wmax = rnd.any(vector<int>{10, 50, 100, 1000});

    // Choose distribution type for diversity
    int dist = rnd.next(0, 2);
    vector<int> v(n);

    if (dist == 0) {
        // Uniform distribution
        for (int i = 0; i < n; i++) {
            v[i] = rnd.next(1, Wmax);
        }
    } else if (dist == 1) {
        // Skewed distribution via weighted next
        int t = rnd.any(vector<int>{-2, -1, 1, 2});
        for (int i = 0; i < n; i++) {
            // rnd.wnext gives [0, Wmax-1], shift to [1, Wmax]
            v[i] = rnd.wnext(Wmax, t) + 1;
        }
    } else {
        // Mostly small numbers with a few large peaks
        int smallLim = min(20, Wmax);
        for (int i = 0; i < n; i++) {
            v[i] = rnd.next(1, smallLim);
        }
        int peaks = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < peaks; i++) {
            int idx = rnd.next(0, n - 1);
            int lo = max(1, Wmax / 2);
            v[idx] = rnd.next(lo, Wmax);
        }
    }

    // Output in required format
    println(n);
    println(v);

    return 0;
}
