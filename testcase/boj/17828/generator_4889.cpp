#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: sometimes minimal, small, or larger up to 10
    int N;
    double rN = rnd.next();
    vector<int> smalls = {2, 3};
    vector<int> larges = {4, 5, 6, 7, 8, 9, 10};
    if (rN < 0.2) {
        N = 1;
    } else if (rN < 0.4) {
        N = rnd.any(smalls);
    } else if (rN < 0.8) {
        N = rnd.any(larges);
    } else {
        N = rnd.next(1, 10);
    }

    // Decide valid or invalid case
    bool makeValid = rnd.next() < 0.75;
    long long X;

    if (makeValid) {
        // For valid, pick X in [N, 26*N], with some bias towards bounds
        long long lo = N, hi = 26LL * N;
        double rc = rnd.next();
        if (rc < 0.3) {
            // close to minimum
            long long mx = min(lo + 5, hi);
            X = rnd.next(lo, mx);
        } else if (rc < 0.6) {
            // close to maximum
            long long mn = max(hi - 5, lo);
            X = rnd.next(mn, hi);
        } else {
            X = rnd.next(lo, hi);
        }
    } else {
        // Invalid: either too small or too large
        bool chooseUnder = (N > 1) && rnd.next() < 0.5;
        if (chooseUnder) {
            // less than N
            X = rnd.next(1, N - 1);
        } else {
            // greater than 26*N
            long long lo = 26LL * N + 1;
            long long hi = lo + rnd.next(1, 5);
            X = rnd.next(lo, hi);
        }
    }

    // Output single test case
    println(N, X);
    return 0;
}
