#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

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

    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(MINC, MAXC, "red_x");
        inf.readSpace();
        long long y = inf.readLong(MINC, MAXC, "red_y");
        inf.readEoln();
        xs[i] = x;
        ys[i] = y;
    }

    for (int i = 0; i < M; ++i) {
        long long x = inf.readLong(MINC, MAXC, "blue_x");
        inf.readSpace();
        long long y = inf.readLong(MINC, MAXC, "blue_y");
        inf.readSpace();
        long long b = inf.readLong(MINB, MAXB, "B_i");
        inf.readEoln();
        xs[N + i] = x;
        ys[N + i] = y;
        (void)b;
    }

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

    auto normDir = [](long long dx, long long dy) {
        long long g = std::gcd(std::llabs(dx), std::llabs(dy));
        dx /= g;
        dy /= g;
        if (dx < 0 || (dx == 0 && dy < 0)) {
            dx = -dx;
            dy = -dy;
        }
        return make_pair(dx, dy);
    };

    struct DirHash {
        size_t operator()(const pair<long long,long long> &p) const {
            uint64_t a = static_cast<uint64_t>(p.first);
            uint64_t b = static_cast<uint64_t>(p.second);
            return static_cast<size_t>((a * 1000003ULL) ^ (b + 0x9e3779b97f4a7c15ULL));
        }
    };

    for (int i = 0; i < total; ++i) {
        unordered_map<pair<long long,long long>, int, DirHash> mp;
        mp.reserve(static_cast<size_t>(total - i - 1) * 2);
        for (int j = i + 1; j < total; ++j) {
            auto d = normDir(xs[j] - xs[i], ys[j] - ys[i]);
            auto it = mp.find(d);
            if (it != mp.end()) {
                ensuref(false,
                        "three collinear points at 0-based indices %d, %d, %d",
                        i, it->second, j);
            }
            mp[d] = j;
        }
    }

    inf.readEof();
}
