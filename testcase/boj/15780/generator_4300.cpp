#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of multitaps K
    int K = rnd.next(1, 10);

    // Generate outlet counts A[i] with bias hyper-parameter t in {-1, 0, 1}
    vector<int> A;
    for (int i = 0; i < K; i++) {
        int t = rnd.any(vector<int>{-1, 0, 1});
        // rnd.wnext(6, t) produces in [0,5], biasing low/high/flat
        int outlets = 3 + rnd.wnext(6, t);
        A.push_back(outlets);
    }

    // Compute total capacity: sum of ceil(A[i] / 2)
    int cap = 0;
    for (int x : A) {
        cap += (x + 1) / 2;
    }

    // Decide whether generate a YES or NO case
    bool enough = rnd.next(0, 1);
    int N;
    if (enough) {
        // 1 <= N <= cap
        N = rnd.next(1, cap);
    } else {
        // cap+1 <= N <= min(cap+5, 100)
        int lo = cap + 1;
        int hi = min(cap + 5, 100);
        // If cap is already >=100, force enough case
        if (lo > hi) {
            N = rnd.next(1, cap);
        } else {
            N = rnd.next(lo, hi);
        }
    }

    // Output
    println(N, K);
    println(A);

    return 0;
}
