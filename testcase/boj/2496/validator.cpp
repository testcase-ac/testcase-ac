#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Helper to check if a point (a,b) is inside/on a D-square
// center (cx,cy), diagonal length K (even).
// A D-square is an axis-aligned square rotated by 45 degrees.
// Condition: |a - cx| + |b - cy| <= K/2
static inline bool inDSquare(long long a, long long b,
                             long long cx, long long cy,
                             long long halfK) {
    long long v = llabs(a - cx) + llabs(b - cy);
    return v <= halfK;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, M, T, K
    long long N = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000LL, "M");
    inf.readSpace();
    int T = inf.readInt(1, 100, "T");
    inf.readSpace();
    long long K = inf.readLong(2LL, 10000000LL, "K");
    inf.readEoln();

    ensuref(K % 2 == 0, "K must be even, got %lld", K);
    long long halfK = K / 2;

    // Read T diamond points, all distinct, within [0,N]x[0,M]
    vector<pair<long long,long long>> pts;
    pts.reserve(T);
    set<pair<long long,long long>> seen;
    for (int i = 0; i < T; ++i) {
        long long A = inf.readLong(0LL, N, "A_i");
        inf.readSpace();
        long long B = inf.readLong(0LL, M, "B_i");
        inf.readEoln();
        pair<long long,long long> p = {A, B};
        ensuref(!seen.count(p), "Duplicate diamond coordinate at index %d: (%lld, %lld)", i, A, B);
        seen.insert(p);
        pts.push_back(p);
    }

    // Now we must validate the *existence* of at least one valid center (X,Y)
    // with integer coordinates, within the map including boundary:
    // 0 <= X <= N, 0 <= Y <= M,
    // such that a D-square of diagonal length K centered at (X,Y)
    // can exist with integer vertices.
    //
    // For a rotated square with diagonal length K, the axis-aligned "radius"
    // is halfK along L1 metric. It is guaranteed by problem that D-square
    // vertices are integer if center is integer and K is even (already checked).

    // Search (brute force over centers is impossible), but we only need to
    // check existence, and the statement guarantees it implicitly by saying
    // we are to choose such a D-square once. The only hard constraint is:
    // center must be within the map including boundary; there is no constraint
    // that the *entire* D-square must lie within [0,N]x[0,M]; only that the
    // center lies on/inside the map.
    //
    // Hence, there always exists at least one integer point (X,Y) in that
    // rectangle [0,N]x[0,M], so we don't need to simulate anything further
    // to guarantee existence of some center.
    //
    // However, we must also validate that the global statement
    // "the answer always exists" holds: given any such input, there must be
    // at least one feasible D-square (i.e., a center X,Y with integer coords
    // within the map) containing some (possibly zero) diamonds. Since
    // [0,N]x[0,M] is non-empty and centers can be any integer point in it,
    // such a square always exists (even if it has 0 diamonds).
    //
    // We still should verify that all computations (like answer size)
    // are within reasonable bounds if we were to solve it, but that's
    // not necessary for validation. There is no further implied global
    // property (e.g., connectivity, non-degeneracy) to check.

    // For additional robustness, we can check that every point is within
    // manhattan distance at most max(N,M)+max(N,M) from some center in map,
    // which is trivial; thus no extra simulation is needed.

    inf.readEof();
}
