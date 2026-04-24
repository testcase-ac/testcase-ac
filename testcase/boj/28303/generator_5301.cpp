#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size hyper-parameter
    int N = rnd.next(2, 10);
    // K hyper-parameter: small, medium, or large
    int kBranch = rnd.next(0, 2);
    int K;
    if (kBranch == 0) K = rnd.next(0, 5);
    else if (kBranch == 1) K = rnd.next(6, 999);
    else K = rnd.next(1000, 2000);

    // Generate array a with different patterns
    vector<int> a(N);
    int pattern = rnd.next(0, 4);
    if (pattern == 0) {
        // all equal
        int v = rnd.next(0, 1000);
        for (int i = 0; i < N; ++i) a[i] = v;
    } else if (pattern == 1) {
        // strictly increasing (small steps)
        int cur = 0;
        for (int i = 0; i < N; ++i) {
            cur += rnd.next(0, 100);
            a[i] = cur;
        }
    } else if (pattern == 2) {
        // strictly decreasing (small steps)
        int cur = 1000;
        for (int i = 0; i < N; ++i) {
            cur -= rnd.next(0, 100);
            if (cur < 0) cur = 0;
            a[i] = cur;
        }
    } else if (pattern == 3) {
        // one large peak among small values
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 1000);
        int idx = rnd.next(0, N - 1);
        a[idx] = rnd.next(1000, 1000000);
    } else {
        // fully random over full range
        for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 1000000000);
    }

    // Optional shuffle to mix positions
    if (rnd.next(0, 1) == 1) {
        shuffle(a.begin(), a.end());
    }

    // Output
    println(N, K);
    println(a);

    return 0;
}
