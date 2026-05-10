#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
    }
};

// Distance squared between two points
static inline long long dist2(long long x1, long long y1, long long x2, long long y2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    return dx * dx + dy * dy;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L, W, N with constraints
    const int L = inf.readInt(1, 50000, "L");
    inf.readSpace();
    const int W = inf.readInt(1, 50000, "W");
    inf.readSpace();
    const int N = inf.readInt(0, 250, "N");
    inf.readEoln();

    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        X[i] = inf.readInt(0, L, "X_i");
        inf.readSpace();
        Y[i] = inf.readInt(0, W, "Y_i");
        inf.readEoln();
    }

    // Now we must validate the global guarantee that the answer always exists.
    // In this problem, the answer is the minimum number of soldiers to remove such that
    // there exists a path from x=0 to x=L staying strictly more than 100m from remaining soldiers.
    //
    // Geometrically, each soldier is a closed disk of radius 100. Prisoners may pass iff
    // there's no continuous chain of overlapping/proximity disks connecting:
    // - left boundary (x=0) to right boundary (x=L), or
    // - bottom boundary (y=0) to top boundary (y=W),
    // such that these chains, together with the boundaries, form barriers separating
    // the start side from the end side.
    //
    // However, the statement does not explicitly *guarantee* that prisoners can always succeed
    // after removing some soldiers; it only asks for minimum removals. There is no upper bound
    // on the answer except N, which is trivially always sufficient (remove all soldiers).
    //
    // Therefore, from a validator's perspective, we do NOT need to check additional geometric
    // global properties; any configuration of soldiers within the given coordinate bounds
    // is a valid input instance.
    //
    // Still, we'll add a basic sanity check related to numerical ranges when reasoning about
    // distances, but we do not reject cases on geometric reachability.

    // Optional geometric sanity check (no rejection; just ensures no overflow if someone reuses code)
    // Maximum coordinate difference is up to 50000, so squared distance fits in 64-bit.
    // 50000^2 * 2 < 2*10^9, far below 2^63.

    // No extra global validation needed per problem statement.

    inf.readEof();
}
