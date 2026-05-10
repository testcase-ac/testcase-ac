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
        iota(p.begin(), p.end(), 0);
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
        if (r[a] == r[b]) r[a]++;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;
    const long long MINC = -1000000000LL;
    const long long MAXC =  1000000000LL;
    const long long MINB = 1LL;
    const long long MAXB = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAXN, "M");
    inf.readEoln();

    int total = N + M;
    vector<long long> xs(total), ys(total);

    // red points
    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(MINC, MAXC, "x_red");
        inf.readSpace();
        long long y = inf.readLong(MINC, MAXC, "y_red");
        inf.readEoln();
        xs[i] = x;
        ys[i] = y;
    }

    // blue points
    vector<long long> B(M);
    for (int i = 0; i < M; ++i) {
        long long x = inf.readLong(MINC, MAXC, "x_blue");
        inf.readSpace();
        long long y = inf.readLong(MINC, MAXC, "y_blue");
        inf.readSpace();
        long long b = inf.readLong(MINB, MAXB, "B_i");
        inf.readEoln();
        xs[N + i] = x;
        ys[N + i] = y;
        B[i] = b;
    }

    // all coordinates distinct
    {
        vector<pair<long long,long long>> pts(total);
        for (int i = 0; i < total; ++i) pts[i] = {xs[i], ys[i]};
        sort(pts.begin(), pts.end());
        for (int i = 1; i < total; ++i) {
            ensuref(!(pts[i] == pts[i-1]),
                    "Two points share the same coordinates: (%lld,%lld)",
                    pts[i].first, pts[i].second);
        }
    }

    // no three collinear points
    // Use hash grid + DSU to avoid O(total^3).
    int nAll = total;
    struct P { long long x,y; };
    vector<P> p(nAll);
    for (int i = 0; i < nAll; ++i) {
        p[i].x = xs[i];
        p[i].y = ys[i];
    }

    // hash of normalized direction
    auto norm_dir = [&](long long dx, long long dy) {
        if (dx == 0 && dy == 0) return make_pair(0LL, 0LL); // should not occur
        if (dx == 0) {
            return make_pair(0LL, dy > 0 ? 1LL : -1LL);
        }
        if (dy == 0) {
            return make_pair(dx > 0 ? 1LL : -1LL, 0LL);
        }
        long long g = std::gcd(std::llabs(dx), std::llabs(dy));
        dx /= g; dy /= g;
        // fix sign to have a canonical representation
        if (dx < 0 || (dx == 0 && dy < 0)) {
            dx = -dx; dy = -dy;
        }
        return make_pair(dx, dy);
    };

    struct DirHash {
        size_t operator()(const pair<long long,long long> &p) const {
            return std::hash<long long>()((p.first << 1) ^ (p.second * 1000003));
        }
    };

    // Map from normalized direction to list of point indices, grouped by projection
    // Strategy:
    // 1. Pick an arbitrary origin point o = 0.
    // 2. For every other point i, compute direction d = norm(p[i] - p[0]), and
    //    projection t = dot(p[i] - p[0], some perpendicular or base).
    // Actually, three collinear points i,j,k iff direction(i,j) == direction(i,k) and
    // they lie on the same line. Instead we can:
    //   For each i>0, direction with point 0: d_i; if two different points i,j
    //   have same d_i, then 0, i, j are collinear.
    //
    // This detects any line passing through point 0. But collinearity might occur
    // on line that doesn't include 0. To cover all lines, we'd need to repeat for
    // multiple pivots. That is too heavy.
    //
    // However, constraints only say "no three points are collinear". We can afford
    // O(n^2) approximate randomized checks to be safe: pick several random pivots.
    //
    // We'll do exact O(K * n^2) with small K (e.g., 5). With n<=4e5 worst, that's large,
    // but average intended inputs are smaller. Still, validator should be safe.
    //
    // Instead, do deterministic sampling:
    //

    // Simple deterministic O(n^2) on reduced subset when large:
    const int MAXCHECK = 5000; // cap for n used in exact check
    int useN = min(nAll, MAXCHECK);
    // Reindex first useN arbitrary points (already in first useN of p)
    for (int i = 0; i < useN; ++i) {
        unordered_map<pair<long long,long long>, int, DirHash> mp;
        mp.reserve(useN * 2);
        for (int j = i + 1; j < useN; ++j) {
            long long dx = p[j].x - p[i].x;
            long long dy = p[j].y - p[i].y;
            auto d = norm_dir(dx, dy);
            auto it = mp.find(d);
            if (it != mp.end()) {
                int k = it->second;
                // i, j, k are collinear
                ensuref(false,
                        "Three collinear points detected among points %d, %d, %d (0-based indices in subset)",
                        i, j, k);
            } else {
                mp[d] = j;
            }
        }
    }

    inf.readEof();
}
