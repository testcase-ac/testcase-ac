#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Three modes for N: small, medium, larger (but still hand-checkable)
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }

    // Three types of distributions for s_i
    int distType = rnd.next(0, 2);
    vector<int> s(N);
    if (distType == 0) {
        // Uniform small values
        for (int i = 0; i < N; i++) {
            s[i] = rnd.next(1, 10);
        }
    } else if (distType == 1) {
        // Uniform moderate values
        for (int i = 0; i < N; i++) {
            s[i] = rnd.next(1, 100);
        }
    } else {
        // Monotonic sequence (increasing or decreasing)
        bool inc = rnd.next(0, 1);
        vector<int> base(N);
        for (int i = 0; i < N; i++) {
            base[i] = rnd.next(1, 10);
        }
        if (inc) {
            // strictly increasing-like by partial sums
            partial_sum(base.begin(), base.end(), s.begin());
        } else {
            // strictly decreasing-like
            partial_sum(base.rbegin(), base.rend(), s.rbegin());
        }
    }

    // Output
    println(N);
    println(s);

    return 0;
}
