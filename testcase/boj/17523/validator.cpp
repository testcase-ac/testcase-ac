#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Line 1: m and n
    int m = inf.readInt(1, 5000, "m");
    inf.readSpace();
    int n = inf.readInt(m, 5000, "n"); // m ≤ n
    inf.readEoln();

    // Line 2: r
    long long r = inf.readLong(1LL, 10000LL, "r");
    inf.readEoln();

    // Line 3: left endpoints L[1..n], strictly increasing
    vector<long long> L = inf.readLongs(n, 0LL, 1000000000LL, "L");
    inf.readEoln();
    for (int i = 0; i + 1 < n; i++) {
        ensuref(L[i] < L[i+1],
                "Left endpoints not strictly increasing at positions %d and %d: L[%d]=%lld, L[%d]=%lld",
                i+1, i+2, i+1, L[i], i+2, L[i+1]);
    }

    // Line 4: S[1..m], sorted indices of start intervals
    vector<int> S = inf.readInts(m, 1, n, "S");
    inf.readEoln();
    for (int i = 0; i + 1 < m; i++) {
        // strictly increasing indices => no duplicates
        ensuref(S[i] < S[i+1],
                "S not strictly increasing at positions %d and %d: %d, %d",
                i+1, i+2, S[i], S[i+1]);
        // intervals in S must not intersect: L[S[i+1]] > L[S[i]] + r
        long long Li = L[S[i]-1], Ri = Li + r;
        long long Lj = L[S[i+1]-1], Rj = Lj + r;
        ensuref(Lj > Ri,
                "Intervals in S intersect at S[%d]=%d ([%lld,%lld]) and S[%d]=%d ([%lld,%lld])",
                i+1, S[i], Li, Ri, i+2, S[i+1], Lj, Rj);
    }

    // Line 5: E[1..m], sorted indices of end intervals
    vector<int> E = inf.readInts(m, 1, n, "E");
    inf.readEoln();
    for (int i = 0; i + 1 < m; i++) {
        ensuref(E[i] < E[i+1],
                "E not strictly increasing at positions %d and %d: %d, %d",
                i+1, i+2, E[i], E[i+1]);
        long long Li = L[E[i]-1], Ri = Li + r;
        long long Lj = L[E[i+1]-1], Rj = Lj + r;
        ensuref(Lj > Ri,
                "Intervals in E intersect at E[%d]=%d ([%lld,%lld]) and E[%d]=%d ([%lld,%lld])",
                i+1, E[i], Li, Ri, i+2, E[i+1], Lj, Rj);
    }

    inf.readEof();
    return 0;
}
