#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Mouse {
    long long px, py, vx, vy;
};

// For given L, check if there exists t >= 0 and a square of side L
// axis-aligned, such that all mice are strictly inside (not on border).
// That is: there exists t >= 0 and (ax, ay) with
// ax < xi(t) < ax + L and ay < yi(t) < ay + L for all i.
// This is equivalent to: width_x(t) < L and width_y(t) < L, where
// width_x(t) = max_i x_i(t) - min_i x_i(t), and similarly for y.
// So "can catch all mice at once" <=> there exists t >= 0 with
// max(width_x(t), width_y(t)) < L.
static bool canCatchAll(const vector<Mouse>& m, long double L) {
    int n = (int)m.size();

    auto evalWidth = [&](long double t, bool xdim)->long double {
        long double mn = 0, mx = 0;
        bool first = true;
        for (int i = 0; i < n; ++i) {
            long double p = xdim ? (long double)m[i].px : (long double)m[i].py;
            long double v = xdim ? (long double)m[i].vx : (long double)m[i].vy;
            long double pos = p + v * t;
            if (first) { mn = mx = pos; first = false; }
            else {
                if (pos < mn) mn = pos;
                if (pos > mx) mx = pos;
            }
        }
        return mx - mn;
    };

    // Collect candidate times where width_x(t) or width_y(t) might attain
    // local minima / change behavior. This includes:
    // - t = 0
    // - intersections of pairwise positions: when x_i(t) == x_j(t) or y_i(t) == y_j(t)
    // Additionally, within each interval between consecutive candidate times,
    // width is piecewise linear, so extreme may happen at boundaries.
    vector<long double> candT;
    candT.push_back(0.0L);

    int nM = n;
    for (int dim = 0; dim < 2; ++dim) {
        for (int i = 0; i < nM; ++i) {
            long double pi = (dim == 0 ? (long double)m[i].px : (long double)m[i].py);
            long double vi = (dim == 0 ? (long double)m[i].vx : (long double)m[i].vy);
            for (int j = i + 1; j < nM; ++j) {
                long double pj = (dim == 0 ? (long double)m[j].px : (long double)m[j].py);
                long double vj = (dim == 0 ? (long double)m[j].vx : (long double)m[j].vy);
                long double dv = vi - vj;
                long double dp = pj - pi;
                if (fabsl(dv) < 1e-18L) continue; // parallel, never meet (or always same).
                long double t = dp / dv;
                if (t >= 0.0L)
                    candT.push_back(t);
            }
        }
    }

    sort(candT.begin(), candT.end());
    candT.erase(unique(candT.begin(), candT.end(), [](long double a, long double b){
        return fabsl(a - b) < 1e-15L;
    }), candT.end());

    auto checkAt = [&](long double t)->bool {
        long double wx = evalWidth(t, true);
        long double wy = evalWidth(t, false);
        long double need = max(wx, wy);
        // Need strictly less than L to place all strictly inside.
        return need < L - 1e-12L; // small epsilon for safety
    };

    // We should inspect candidate times and midpoints between them (since
    // extrema of piecewise linear envelope can occur at pairwise intersection times).
    int sz = (int)candT.size();
    for (int i = 0; i < sz; ++i) {
        long double t = candT[i];
        if (t < 0.0L) continue;
        if (checkAt(t)) return true;
        // midpoint to next if finite distance
        if (i + 1 < sz) {
            long double tmid = (candT[i] + candT[i + 1]) * 0.5L;
            if (tmid >= 0.0L && checkAt(tmid)) return true;
        }
    }

    // Additionally, check a "large" time if velocities diverge so min occurs at infinity.
    // Practically, we can check some big factor of max candidate time.
    long double maxT = 0.0L;
    for (long double t : candT) if (t > maxT) maxT = t;
    long double bigT = maxT * 2.0L + 10.0L;
    if (bigT >= 0.0L && checkAt(bigT)) return true;

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    vector<Mouse> mice(N);
    for (int i = 0; i < N; ++i) {
        long long px = inf.readLong(-1000LL, 1000LL, "px");
        inf.readSpace();
        long long py = inf.readLong(-1000LL, 1000LL, "py");
        inf.readSpace();
        long long vx = inf.readLong(-1000LL, 1000LL, "vx");
        inf.readSpace();
        long long vy = inf.readLong(-1000LL, 1000LL, "vy");
        inf.readEoln();
        mice[i] = {px, py, vx, vy};
    }

    // Global property from statement:
    // "한 번에 모든 쥐를 절대로 잡을 수 없는 가장 큰 L" is finite and well-defined.
    // For very large L, it is always possible to catch all at once (at t = 0, take
    // L >= max(width_x(0), width_y(0))); hence the "largest L where impossible"
    // must be >= 0 and < some bound. We verify that:
    // - For some reasonably large L, catching is possible.
    // - For some small L (e.g., 0), catching is impossible.
    // This ensures the required threshold exists.
    long double wx0, wy0;
    {
        long double mnx = mice[0].px, mxx = mice[0].px;
        long double mny = mice[0].py, mxy = mice[0].py;
        for (int i = 1; i < N; ++i) {
            mnx = min(mnx, (long double)mice[i].px);
            mxx = max(mxx, (long double)mice[i].px);
            mny = min(mny, (long double)mice[i].py);
            mxy = max(mxy, (long double)mice[i].py);
        }
        wx0 = mxx - mnx;
        wy0 = mxy - mny;
    }

    long double baseL = max(wx0, wy0) + 10.0L; // if L >= baseL, definitely can at t = 0
    ensuref(canCatchAll(mice, baseL),
            "Global property failed: even for large L=%Lf all mice cannot be captured at once.", (double)baseL);

    ensuref(!canCatchAll(mice, 0.0L),
            "Global property failed: for L=0 it's incorrectly possible to capture all mice.");

    inf.readEof();
}
