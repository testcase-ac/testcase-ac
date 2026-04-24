#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Fenwick / BIT for point updates and range sum queries.
struct BIT {
    int n;
    vector<int> t;
    BIT(int _n): n(_n), t(n+1, 0) {}
    // add v at position i (1-based)
    void add(int i, int v) {
        for (; i <= n; i += i & -i) t[i] += v;
    }
    // sum of [1..i]
    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    // sum of [l..r], 1-based
    int sum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l-1);
    }
    // find smallest i such that sum(i) >= target; if none, returns n+1
    int lower_bound(int target) const {
        int pos = 0;
        int maxb = 1 << (31 - __builtin_clz(n));
        for (int b = maxb; b > 0; b >>= 1) {
            int np = pos + b;
            if (np <= n && t[np] < target) {
                target -= t[np];
                pos = np;
            }
        }
        return pos + 1;
    }
};

struct HSeg { int y, x1, x2, idx; };
struct VSeg { int x, y1, y2, idx; };
struct Event {
    int x, type; 
    // type: 0 = add H, 1 = query V, 2 = remove H
    int y;        // for H
    int y1, y2;   // for V
    int vidx;     // for V
    int hidx;     // for H
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W, H
    int W = inf.readInt(1, 200000, "W");
    inf.readSpace();
    int H = inf.readInt(1, 200000, "H");
    inf.readEoln();

    // Read N
    int N = inf.readInt(3, 500000, "N");
    inf.readEoln();

    // Read polygon vertices
    vector<pair<int,int>> pts(N);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, W, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, H, "y_i");
        inf.readEoln();
        pts[i] = {x,y};
    }

    // Check no duplicate vertices
    {
        auto tmp = pts;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < N; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate vertex at (%d, %d)", tmp[i].first, tmp[i].second);
        }
    }

    // Check orientation (shoelace): should be CCW => area > 0
    {
        long long s = 0;
        for (int i = 0; i < N; i++) {
            auto [x1,y1] = pts[i];
            auto [x2,y2] = pts[(i+1)%N];
            s += (long long)x1 * y2 - (long long)x2 * y1;
        }
        ensuref(s > 0, "Polygon vertices are not in CCW order or area is non-positive");
    }

    // Build horizontal and vertical segments
    vector<HSeg> hs;
    vector<VSeg> vs;
    hs.reserve(N);
    vs.reserve(N);
    for (int i = 0; i < N; i++) {
        auto [x1,y1] = pts[i];
        auto [x2,y2] = pts[(i+1)%N];
        // no zero-length
        ensuref(!(x1==x2 && y1==y2),
                "Zero-length edge at index %d: (%d,%d)-(%d,%d)", i, x1,y1, x2,y2);
        if (y1 == y2) {
            // horizontal
            int lx = min(x1, x2);
            int rx = max(x1, x2);
            ensuref(rx > lx,
                    "Zero-length horizontal edge at index %d", i);
            hs.push_back({y1, lx, rx, i});
        } else if (x1 == x2) {
            // vertical
            int ly = min(y1, y2);
            int ry = max(y1, y2);
            ensuref(ry > ly,
                    "Zero-length vertical edge at index %d", i);
            vs.push_back({x1, ly, ry, i});
        } else {
            ensuref(false,
                    "Edge %d is not axis-aligned: (%d,%d)-(%d,%d)",
                    i, x1,y1, x2,y2);
        }
    }

    // Check overlapping horizontals
    {
        auto v = hs;
        sort(v.begin(), v.end(), [](auto &a, auto &b){
            if (a.y != b.y) return a.y < b.y;
            return a.x1 < b.x1;
        });
        int prevY = INT_MIN, prevEnd = INT_MIN, prevIdx = -1;
        for (auto &s : v) {
            if (s.y != prevY) {
                prevY = s.y;
                prevEnd = s.x2;
                prevIdx = s.idx;
            } else {
                if (s.x1 < prevEnd) {
                    ensuref(false,
                        "Overlapping horizontal edges at y=%d between indices %d and %d",
                        s.y, prevIdx, s.idx);
                }
                if (s.x1 == prevEnd) {
                    bool adj = ((prevIdx+1)%N == s.idx) ||
                               ((s.idx+1)%N == prevIdx);
                    ensuref(adj,
                        "Touching horizontal edges at y=%d but not adjacent: indices %d and %d",
                        s.y, prevIdx, s.idx);
                }
                prevEnd = s.x2;
                prevIdx = s.idx;
            }
        }
    }

    // Check overlapping verticals
    {
        auto v = vs;
        sort(v.begin(), v.end(), [](auto &a, auto &b){
            if (a.x != b.x) return a.x < b.x;
            return a.y1 < b.y1;
        });
        int prevX = INT_MIN, prevEnd = INT_MIN, prevIdx = -1;
        for (auto &s : v) {
            if (s.x != prevX) {
                prevX = s.x;
                prevEnd = s.y2;
                prevIdx = s.idx;
            } else {
                if (s.y1 < prevEnd) {
                    ensuref(false,
                        "Overlapping vertical edges at x=%d between indices %d and %d",
                        s.x, prevIdx, s.idx);
                }
                if (s.y1 == prevEnd) {
                    bool adj = ((prevIdx+1)%N == s.idx) ||
                               ((s.idx+1)%N == prevIdx);
                    ensuref(adj,
                        "Touching vertical edges at x=%d but not adjacent: indices %d and %d",
                        s.x, prevIdx, s.idx);
                }
                prevEnd = s.y2;
                prevIdx = s.idx;
            }
        }
    }

    // Prepare sweep-line events to detect non-adjacent crossings
    vector<Event> evs;
    evs.reserve(hs.size()*2 + vs.size());
    for (auto &h : hs) {
        evs.push_back({h.x1, 0, h.y, 0,0,0, h.idx});
        evs.push_back({h.x2, 2, h.y, 0,0,0, h.idx});
    }
    for (auto &v : vs) {
        evs.push_back({v.x, 1, 0, v.y1, v.y2, v.idx, 0});
    }
    sort(evs.begin(), evs.end(), [](auto &a, auto &b){
        if (a.x != b.x) return a.x < b.x;
        return a.type < b.type;
    });

    // BIT over y=0..H maps to indices 1..H+1
    BIT bit(H+1);
    vector<int> activeH(H+1, -1);
    // For lookup horizontal data by idx
    vector<HSeg> hByIdx(N);
    for (auto &h : hs) hByIdx[h.idx] = h;

    for (auto &e : evs) {
        if (e.type == 0) {
            // add horizontal
            int y = e.y;
            int idy = y + 1;
            ensuref(activeH[y] == -1,
                    "Horizontal segment %d at y=%d already active", e.hidx, y);
            activeH[y] = e.hidx;
            bit.add(idy, +1);
        } else if (e.type == 2) {
            // remove horizontal
            int y = e.y;
            int idy = y + 1;
            ensuref(activeH[y] == e.hidx,
                    "Removing horizontal segment %d at y=%d but active is %d",
                    e.hidx, y, activeH[y]);
            activeH[y] = -1;
            bit.add(idy, -1);
        } else {
            // query vertical: detect any intersection in interior (y1,y2)
            int y1 = e.y1, y2 = e.y2, vidx = e.vidx;
            // interior y-range: y1+1 .. y2-1
            int low_y = y1 + 1;
            int high_y = y2 - 1;
            if (low_y <= high_y) {
                int id_low = low_y + 1;   // map to bit-index
                int id_high = high_y + 1;
                int cnt = bit.sum(id_low, id_high);
                if (cnt > 0) {
                    // find one crossing horizontal
                    int before = bit.sum(1, id_low-1);
                    int pos = bit.lower_bound(before + 1);
                    int y_cross = pos - 1;
                    int hidx = activeH[y_cross];
                    auto &hseg = hByIdx[hidx];
                    // crossing at (e.x, y_cross)
                    ensuref(false,
                        "Edge crossing between non-adjacent segments %d (horizontal y=%d x=[%d,%d]) and %d (vertical x=%d y=[%d,%d]) at (%d,%d)",
                        hidx, hseg.y, hseg.x1, hseg.x2,
                        vidx, e.x, y1, y2, e.x, y_cross);
                }
            }
        }
    }

    // final EOF
    inf.readEof();
    return 0;
}
