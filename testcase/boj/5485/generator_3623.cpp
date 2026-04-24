#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of average sequence
    int n = rnd.next(2, 10);
    // Base maximum for starting value
    int maxVal = rnd.next(0, 100);
    // Hyper-parameter for maximum increment
    int v3 = rnd.next(1, 5);
    int v4 = rnd.next(1, 20);
    vector<int> maxIncOpts = {0, 1, v3, v4};
    int maxInc = rnd.any(maxIncOpts);
    // Hyper-parameter for distribution skew
    vector<int> skew = {-1, 0, 1};
    int t = rnd.any(skew);

    // Generate non-decreasing integer m[1..n]
    vector<long long> m(n);
    m[0] = rnd.next(0, maxVal);
    for (int i = 1; i < n; i++) {
        // r in [0..maxInc], skewed by t
        int r = rnd.wnext(maxInc + 1, t);
        m[i] = m[i-1] + r;
    }

    // Output
    println(n);
    for (auto x : m) {
        println(x);
    }
    return 0;
}
