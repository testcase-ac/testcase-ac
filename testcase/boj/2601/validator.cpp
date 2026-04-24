#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    int yl, yr; // indices in compressed y for open interval (y2, y1)
};

int Nseg;
vector<int> seg, lazy;

void push(int node) {
    if (lazy[node] != 0) {
        int v = lazy[node];
        int lc = node << 1, rc = lc | 1;
        seg[lc] += v;
        lazy[lc] += v;
        seg[rc] += v;
        lazy[rc] += v;
        lazy[node] = 0;
    }
}

void updateRange(int node, int l, int r, int ql, int qr, int val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        seg[node] += val;
        lazy[node] += val;
        return;
    }
    push(node);
    int mid = (l + r) >> 1;
    updateRange(node<<1, l, mid, ql, qr, val);
    updateRange(node<<1|1, mid+1, r, ql, qr, val);
    seg[node] = max(seg[node<<1], seg[node<<1|1]);
}

int queryMax(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) {
        return seg[node];
    }
    push(node);
    int mid = (l + r) >> 1;
    return max(queryMax(node<<1, l, mid, ql, qr),
               queryMax(node<<1|1, mid+1, r, ql, qr));
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: room rectangle
    int rx1 = inf.readInt(0, 999999, "room_x1");
    inf.readSpace();
    int ry1 = inf.readInt(0, 999999, "room_y1");
    inf.readSpace();
    int rx2 = inf.readInt(0, 999999, "room_x2");
    inf.readSpace();
    int ry2 = inf.readInt(0, 999999, "room_y2");
    inf.readEoln();
    // Validate room rectangle orientation and size
    ensuref(rx1 < rx2, "room_x1 (%d) must be < room_x2 (%d)", rx1, rx2);
    ensuref(ry2 < ry1, "room_y2 (%d) must be < room_y1 (%d)", ry2, ry1);
    int room_w = rx2 - rx1;
    int room_h = ry1 - ry2;
    ensuref(room_w < 1000000, "room width %d must be < 1000000", room_w);
    ensuref(room_h < 1000000, "room height %d must be < 1000000", room_h);

    // Second line: carpet length
    int L = inf.readInt(1, 999999, "carpet_length");
    inf.readEoln();
    // Carpet must fit in room
    ensuref(L <= room_w, "carpet_length %d exceeds room width %d", L, room_w);
    ensuref(L <= room_h, "carpet_length %d exceeds room height %d", L, room_h);

    // Third line: number of stains
    int N = inf.readInt(0, 100000, "n");
    inf.readEoln();

    vector<Rect> R(N);
    vector<int> ys;
    ys.reserve(2 * N);
    for (int i = 0; i < N; i++) {
        int x1 = inf.readInt(0, 999999, "x1_i");
        inf.readSpace();
        int y1 = inf.readInt(0, 999999, "y1_i");
        inf.readSpace();
        int x2 = inf.readInt(0, 999999, "x2_i");
        inf.readSpace();
        int y2 = inf.readInt(0, 999999, "y2_i");
        inf.readEoln();
        // orientation and positive sizes
        ensuref(x1 < x2, "stain %d: x1 (%d) must be < x2 (%d)", i, x1, x2);
        ensuref(y2 < y1, "stain %d: y2 (%d) must be < y1 (%d)", i, y2, y1);
        // size limits
        ensuref(x2 - x1 < 1000000, "stain %d width %d must be < 1000000", i, x2-x1);
        ensuref(y1 - y2 < 1000000, "stain %d height %d must be < 1000000", i, y1-y2);
        // containment in room
        ensuref(x1 >= rx1 && x2 <= rx2,
                "stain %d: x-range [%d,%d] not within room x [%d,%d]",
                i, x1, x2, rx1, rx2);
        ensuref(y1 <= ry1 && y2 >= ry2,
                "stain %d: y-range [%d,%d] not within room y [%d,%d]",
                i, y2, y1, ry2, ry1);
        R[i].x1 = x1;
        R[i].x2 = x2;
        R[i].y1 = y1;
        R[i].y2 = y2;
        ys.push_back(y2);
        ys.push_back(y1);
    }

    // Check non-overlapping stains via sweep line and segment tree
    if (N > 1) {
        // compress y
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int M = ys.size();
        // We build segments on open intervals between ys[k] and ys[k+1], indices [0..M-2]
        Nseg = max(0, M - 1);
        if (Nseg > 0) {
            seg.assign(4 * Nseg + 4, 0);
            lazy.assign(4 * Nseg + 4, 0);
            // assign yl, yr for each rect
            for (int i = 0; i < N; i++) {
                int y2 = R[i].y2, y1 = R[i].y1;
                int li = int(lower_bound(ys.begin(), ys.end(), y2) - ys.begin());
                int ri = int(lower_bound(ys.begin(), ys.end(), y1) - ys.begin());
                // interior open interval is (y2, y1) => segments [li .. ri-1]
                R[i].yl = li;
                R[i].yr = ri;
            }
            // events: (x, type, idx). type 0=removal,1=add
            struct Evt { int x, type, id; };
            vector<Evt> ev;
            ev.reserve(2*N);
            for (int i = 0; i < N; i++) {
                ev.push_back({R[i].x1, 1, i});
                ev.push_back({R[i].x2, 0, i});
            }
            sort(ev.begin(), ev.end(), [](const Evt &a, const Evt &b){
                if (a.x != b.x) return a.x < b.x;
                return a.type < b.type; // removal (0) before add (1)
            });
            for (auto &e : ev) {
                int id = e.id;
                int l = R[id].yl;
                int r = R[id].yr - 1;
                if (e.type == 0) {
                    // remove
                    if (l <= r)
                        updateRange(1, 0, Nseg-1, l, r, -1);
                } else {
                    // add: check overlap
                    if (l <= r) {
                        int mx = queryMax(1, 0, Nseg-1, l, r);
                        ensuref(mx == 0,
                                "stains %d and some active one overlap in y-range (%.0f,%.0f)",
                                id, double(R[id].y2), double(R[id].y1));
                        updateRange(1, 0, Nseg-1, l, r, +1);
                    }
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
