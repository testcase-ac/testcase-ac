#include "testlib.h"
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <cstdint>
using namespace std;

struct Pt {
    int x, y;
};

int orientation(const Pt &a, const Pt &b, const Pt &c) {
    // returns 0 if colinear, 1 if clockwise, 2 if counterclockwise
    long long v = (long long)(b.y - a.y) * (c.x - b.x)
                - (long long)(b.x - a.x) * (c.y - b.y);
    if (v == 0) return 0;
    return (v > 0) ? 1 : 2;
}

bool onSegment(const Pt &a, const Pt &b, const Pt &p) {
    // check if p lies on segment ab (assuming colinearity)
    return p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x)
        && p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}

bool segmentsIntersect(const Pt &p1, const Pt &p2, const Pt &p3, const Pt &p4) {
    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);
    // general case
    if (o1 != o2 && o3 != o4) return true;
    // special colinear cases
    if (o1 == 0 && onSegment(p1, p2, p3)) return true;
    if (o2 == 0 && onSegment(p1, p2, p4)) return true;
    if (o3 == 0 && onSegment(p3, p4, p1)) return true;
    if (o4 == 0 && onSegment(p3, p4, p2)) return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments
    int F = inf.readInt(3, 1000, "F");
    inf.readEoln();

    vector<pair<Pt,Pt>> segs;
    segs.reserve(F);
    set<pair<pair<int,int>,pair<int,int>>> segset;

    for (int i = 0; i < F; i++) {
        int x1 = inf.readInt(0, 1000, "x1_i");
        inf.readSpace();
        int y1 = inf.readInt(0, 1000, "y1_i");
        inf.readSpace();
        int x2 = inf.readInt(0, 1000, "x2_i");
        inf.readSpace();
        int y2 = inf.readInt(0, 1000, "y2_i");
        inf.readEoln();

        // Zero-length check
        ensuref(!(x1 == x2 && y1 == y2),
                "Zero-length segment at index %d: (%d,%d)-(%d,%d)",
                i, x1, y1, x2, y2);

        // Check duplicate segments
        pair<int,int> p1 = make_pair(x1, y1);
        pair<int,int> p2 = make_pair(x2, y2);
        pair<pair<int,int>,pair<int,int>> key =
            (p1 < p2) ? make_pair(p1, p2) : make_pair(p2, p1);
        ensuref(!segset.count(key),
                "Duplicate segment at index %d: (%d,%d)-(%d,%d)",
                i, x1, y1, x2, y2);
        segset.insert(key);

        segs.push_back({ Pt{x1,y1}, Pt{x2,y2} });
    }

    // Check for intersections
    for (int i = 0; i < F; i++) {
        for (int j = i+1; j < F; j++) {
            const Pt &a1 = segs[i].first;
            const Pt &a2 = segs[i].second;
            const Pt &b1 = segs[j].first;
            const Pt &b2 = segs[j].second;
            // skip if they share an endpoint
            bool share = (a1.x==b1.x && a1.y==b1.y)
                      || (a1.x==b2.x && a1.y==b2.y)
                      || (a2.x==b1.x && a2.y==b1.y)
                      || (a2.x==b2.x && a2.y==b2.y);
            if (share) continue;
            if (segmentsIntersect(a1,a2,b1,b2)) {
                ensuref(false,
                        "Segments %d and %d intersect: (%d,%d)-(%d,%d) and (%d,%d)-(%d,%d)",
                        i, j,
                        a1.x, a1.y, a2.x, a2.y,
                        b1.x, b1.y, b2.x, b2.y);
            }
        }
    }

    // Build graph: map points to vertex ids
    map<pair<int,int>, int> vid;
    int vcnt = 0;
    vector<pair<int,int>> edges; // (u,v) per segment index
    edges.reserve(F);
    for (int i = 0; i < F; i++) {
        auto &p1 = segs[i].first;
        auto &p2 = segs[i].second;
        pair<int,int> pp1 = make_pair(p1.x, p1.y);
        pair<int,int> pp2 = make_pair(p2.x, p2.y);
        if (!vid.count(pp1)) vid[pp1] = vcnt++;
        if (!vid.count(pp2)) vid[pp2] = vcnt++;
        int u = vid[pp1], v = vid[pp2];
        edges.emplace_back(u, v);
    }

    // adjacency list with edge indices
    vector<vector<pair<int,int>>> adj(vcnt);
    for (int i = 0; i < F; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // Check connectivity via BFS
    vector<char> vis(vcnt, 0);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    int seen = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &pr : adj[u]) {
            int v = pr.first;
            if (!vis[v]) {
                vis[v] = 1;
                seen++;
                q.push(v);
            }
        }
    }
    ensuref(seen == vcnt, "Graph is disconnected: only %d of %d vertices reachable",
            seen, vcnt);

    // Check for bridges (no segment is a bridge)
    vector<int> disc(vcnt, -1), low(vcnt, -1);
    vector<char> visited(vcnt, 0);
    int timer = 0;

    function<void(int,int)> dfs = [&](int u, int peid) {
        visited[u] = 1;
        disc[u] = low[u] = timer++;
        for (auto &pr : adj[u]) {
            int v = pr.first, eid = pr.second;
            if (eid == peid) continue;
            if (!visited[v]) {
                dfs(v, eid);
                low[u] = min(low[u], low[v]);
                // if this edge is a bridge
                if (low[v] > disc[u]) {
                    ensuref(false,
                            "Bridge detected at segment index %d: connects vertices %d and %d",
                            eid, u, v);
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };

    dfs(0, -1);

    inf.readEof();
    return 0;
}
