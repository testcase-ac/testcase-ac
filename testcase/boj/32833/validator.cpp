#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <string>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

// Helper to generate variable names for error messages
string varname(const char* base, int idx) {
    return string(base) + "_" + to_string(idx);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(4, 100000, "n");
    ensuref(n % 2 == 0, "n must be even, got %d", n);
    inf.readEoln();

    // 2. Read v[0..n-1]
    vector<ll> v(n);
    v[0] = inf.readLong(0LL, 0LL, "v_1"); // v_1 = 0
    inf.readSpace();
    for (int i = 1; i < n - 1; ++i) {
        v[i] = inf.readLong(0LL, 1000000LL, varname("v", i + 1).c_str());
        inf.readSpace();
    }
    v[n - 1] = inf.readLong(0LL, 0LL, "v_n"); // v_n = 0
    inf.readEoln();

    // 3. Read S and T
    ll s_x = inf.readLong(-1000000LL, 2000000LL, "s_x");
    inf.readSpace();
    ll s_y = inf.readLong(-1000000LL, 2000000LL, "s_y");
    inf.readSpace();
    ll t_x = inf.readLong(1LL, 999999LL, "t_x"); // 0 < t_x < 10^6
    inf.readSpace();
    ll t_y = inf.readLong(1LL, 999999LL, "t_y"); // 0 < t_y < 10^6
    inf.readEoln();

    // 4. Check x-coordinates strictly increasing for vertical edges
    // The vertical edges are at even indices: 0,2,4,...,n-2
    for (int i = 2; i < n; i += 2) {
        ensuref(v[i] > v[i - 2],
            "x-coordinates must be strictly increasing at v[%d]=%lld, v[%d]=%lld",
            i + 1, v[i], i - 1 + 1, v[i - 2]);
    }

    // 5. Check edge lengths >= 1 and reconstruct the polygon
    // The sequence alternates: x0=0, y1, x1, y2, x2, ..., x_{n/2}, 0
    // So: (x0,0), (x0,y1), (x1,y1), (x1,y2), (x2,y2), ..., (x_{n/2},0)
    vector<pll> pts;
    ll cur_x = v[0], cur_y = 0;
    pts.emplace_back(cur_x, cur_y); // (x0, 0)
    for (int i = 1; i < n - 1; ++i) {
        if (i % 2 == 1) {
            // y-coordinate: vertical edge
            ll new_y = v[i];
            ensuref(abs(new_y - cur_y) >= 1,
                "Vertical edge at index %d has length < 1: |%lld - %lld|",
                i + 1, new_y, cur_y);
            cur_y = new_y;
        } else {
            // x-coordinate: horizontal edge
            ll new_x = v[i];
            ensuref(abs(new_x - cur_x) >= 1,
                "Horizontal edge at index %d has length < 1: |%lld - %lld|",
                i + 1, new_x, cur_x);
            cur_x = new_x;
        }
        pts.emplace_back(cur_x, cur_y);
    }
    // End at (v[n-1], 0)
    pts.emplace_back(v[n - 2], 0LL); // The base segment's right endpoint
    // The last v[n-1]=0 is just for input format, not a real vertex.

    // 6. Check base segment is valid (left < right)
    ll base_left = v[0];
    ll base_right = v[n - 2];
    ensuref(base_left < base_right,
        "Base segment must have positive length: left=%lld, right=%lld",
        base_left, base_right);

    // 7. Check no duplicate consecutive vertices (degenerate edge)
    for (int i = 1; i < (int)pts.size(); ++i) {
        ensuref(!(pts[i].first == pts[i - 1].first && pts[i].second == pts[i - 1].second),
            "Degenerate edge: consecutive vertices %d and %d are identical: (%lld,%lld)",
            i - 1, i, pts[i].first, pts[i].second);
    }

    // 8. Check polygon is non-degenerate (area > 0)
    // Shoelace formula
    long double area = 0.0;
    int m = pts.size();
    for (int i = 0; i < m; ++i) {
        area += (long double)pts[i].first * (long double)pts[(i + 1) % m].second;
        area -= (long double)pts[i].second * (long double)pts[(i + 1) % m].first;
    }
    area = fabsl(area) / 2.0;
    ensuref(area > 0.0, "Polygon area must be positive, got %.10Lf", area);

    // 9. Check S is outside the histogram, T is inside and not on boundary

    // Point on segment
    auto point_on_segment = [](ll x, ll y, pll a, pll b) -> bool {
        ll minx = min(a.first, b.first), maxx = max(a.first, b.first);
        ll miny = min(a.second, b.second), maxy = max(a.second, b.second);
        if (x < minx || x > maxx || y < miny || y > maxy) return false;
        // Check colinearity
        ll dx1 = b.first - a.first, dy1 = b.second - a.second;
        ll dx2 = x - a.first, dy2 = y - a.second;
        return dx1 * dy2 == dy1 * dx2;
    };

    // Point in polygon: 0=outside, 1=on boundary, 2=inside
    auto point_in_polygon = [&](ll x, ll y) -> int {
        int cnt = 0;
        int m = pts.size();
        for (int i = 0; i < m; ++i) {
            pll a = pts[i], b = pts[(i + 1) % m];
            if (point_on_segment(x, y, a, b)) return 1;
            // Ray casting: count crossings of horizontal ray to the right
            if (a.second == b.second) continue; // horizontal edge
            if (y < min(a.second, b.second)) continue;
            if (y >= max(a.second, b.second)) continue;
            // Compute intersection x-coordinate
            long double xint = a.first + (long double)(b.first - a.first) * (y - a.second) / (b.second - a.second);
            if (xint > x) cnt++;
        }
        return (cnt % 2 == 1) ? 2 : 0;
    };

    int t_pos = point_in_polygon(t_x, t_y);
    ensuref(t_pos == 2, "T = (%lld,%lld) must be strictly inside the polygon, not on boundary (pos=%d)", t_x, t_y, t_pos);

    int s_pos = point_in_polygon(s_x, s_y);
    ensuref(s_pos == 0, "S = (%lld,%lld) must be strictly outside the polygon (pos=%d)", s_x, s_y, s_pos);

    inf.readEof();
}
