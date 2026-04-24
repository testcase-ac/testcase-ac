#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: sometimes extreme 1 or 100, otherwise weighted
    int pick = rnd.next(1, 10);
    int N;
    if (pick == 1) {
        N = 1;
    } else if (pick == 2) {
        N = 100;
    } else {
        // weighted to get small, medium, or large N
        vector<int> tvals = {-3, -2, -1, 0, 1, 2, 3};
        int t = rnd.any(tvals);
        N = rnd.wnext(100, t) + 1;  // [1..100]
    }
    // Minimum sum required to have N distinct positive integers
    long long base = 1LL * N * (N + 1) / 2;
    // Constraints: K in [100, 1e6]
    long long Klow = max(base, 100LL);
    long long Khigh = 1000000LL;
    long long maxExtra = Khigh - Klow;
    // Hyper-parameter for extra: sometimes small extra, sometimes large
    vector<int> ev = {-3, -2, -1, 0, 1, 2, 3};
    int te = rnd.any(ev);
    long long extra = rnd.wnext(maxExtra + 1, te); // [0..maxExtra]
    long long K = Klow + extra;
    // Output one test case
    println(K);
    println(N);
    return 0;
}
