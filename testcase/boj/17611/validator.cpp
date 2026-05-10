#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct HSeg {
    int idxEdge;
    ll x1, x2, y;
};
struct VSeg {
    int idxEdge;
    ll x, y1, y2;
};
struct Event {
    ll x;
    int type; // 0 = add H, 1 = query V, 2 = remove H
    int idx;  // index into HSegs for add/remove, into VSegs for query
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(4, 100000, "n");
    inf.readEoln();

    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = inf.readLong(-500000LL, 500000LL, "x_i");
        inf.readSpace();
        y[i] = inf.readLong(-500000LL, 500000LL, "y_i");
        inf.readEoln();
    }

    // Check distinct vertices
    {
        set<pair<ll,ll>> vs;
        for (int i = 0; i < n; i++) {
            auto p = make_pair(x[i], y[i]);
            ensuref(!vs.count(p), "Duplicate vertex at index %d: (%lld, %lld)", i, x[i], y[i]);
            vs.insert(p);
        }
    }

    // Check edges are axis-aligned, non-zero length, collect segments
    vector<HSeg> H;
    vector<VSeg> V;
    H.reserve(n);
    V.reserve(n);
    for (int i = 0; i < n; i++) {
        int j = (i+1) % n;
        bool sameX = (x[i] == x[j]);
        bool sameY = (y[i] == y[j]);
        ensuref(sameX ^ sameY,
                "Edge %d -> %d is not a non-zero axis-aligned segment: (%lld,%lld)-(%lld,%lld)",
                i, j, x[i], y[i], x[j], y[j]);
        if (sameY) {
            // horizontal
            HSeg h;
            h.idxEdge = i;
            h.y = y[i];
            h.x1 = min(x[i], x[j]);
            h.x2 = max(x[i], x[j]);
            H.push_back(h);
        } else {
            // vertical
            VSeg v;
            v.idxEdge = i;
            v.x = x[i];
            v.y1 = min(y[i], y[j]);
            v.y2 = max(y[i], y[j]);
            V.push_back(v);
        }
    }

    // Check orientation is clockwise: area sum < 0
    {
        __int128 area2 = 0;
        for (int i = 0; i < n; i++) {
            int j = (i+1) % n;
            area2 += (__int128)x[i] * y[j] - (__int128)x[j] * y[i];
        }
        ensuref(area2 < 0, "Polygon vertices are not in clockwise order");
    }

    // Build sweep events
    vector<Event> evs;
    evs.reserve(H.size()*2 + V.size());
    for (int i = 0; i < (int)H.size(); i++) {
        evs.push_back({H[i].x1, 0, i});
        evs.push_back({H[i].x2, 2, i});
    }
    for (int i = 0; i < (int)V.size(); i++) {
        evs.push_back({V[i].x, 1, i});
    }
    sort(evs.begin(), evs.end(), [](const Event &a, const Event &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.type < b.type; // add(0), query(1), remove(2)
    });

    // Active horizontals by (y, idxEdge)
    multiset<pair<ll,int>> active;

    // Sweep
    for (auto &e : evs) {
        if (e.type == 0) {
            // add horizontal
            auto &h = H[e.idx];
            active.insert({h.y, h.idxEdge});
        } else if (e.type == 2) {
            // remove horizontal
            auto &h = H[e.idx];
            auto it = active.find({h.y, h.idxEdge});
            ensuref(it != active.end(),
                    "Internal error: horizontal segment not found on removal");
            active.erase(it);
        } else {
            // query vertical
            auto &v = V[e.idx];
            // find horizontals with y in [y1, y2]
            auto it = active.lower_bound({v.y1, -1});
            while (it != active.end() && it->first <= v.y2) {
                ll yh = it->first;
                int ih = it->second;
                int iv = v.idxEdge;
                bool adj = ( (ih + 1) % n == iv ) || ( (iv + 1) % n == ih );
                if (!adj) {
                    ensuref(false,
                            "Non-adjacent intersection between h-edge %d and v-edge %d at (%lld,%lld)",
                            ih, iv, v.x, yh);
                }
                ++it;
            }
        }
    }

    inf.readEof();
    return 0;
}
