#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 3 and 10
    int N = rnd.next(3, 10);
    vector<int> M(N);

    // Hyper-parameter: pick a distribution type
    // 0 = uniform in [1, H]
    // 1 = biased via wnext (skewed low or high)
    // 2 = monotonic sequence (increasing or decreasing)
    int distType = rnd.next(0, 2);

    if (distType == 0) {
        // Uniform between 1 and a random upper bound
        int high = rnd.next(1, 10000);
        for (int i = 0; i < N; i++) {
            M[i] = rnd.next(1, high);
        }
    } else if (distType == 1) {
        // Biased distribution via wnext
        // t > 0 skews toward higher values, t < 0 toward lower
        int t = rnd.next(-3, 3);
        for (int i = 0; i < N; i++) {
            // rnd.wnext(10000, t) returns [0..9999], shift to [1..10000]
            M[i] = rnd.wnext(10000, t) + 1;
        }
    } else {
        // Monotonic sequence, then maybe reversed
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < N; i++) {
            int step = rnd.next(0, 1000);
            cur = min(cur + step, 10000);
            M[i] = cur;
        }
        if (rnd.next(0, 1) == 0) {
            reverse(M.begin(), M.end());
        }
    }

    // Output the test case
    println(N);
    for (int x : M) {
        println(x);
    }

    return 0;
}
