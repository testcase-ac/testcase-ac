#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Bus {
    int id;
    int x1, y1, x2, y2;
    bool horizontal; // true if y1 == y2
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_MN = 100000;
    const int MAX_K  = 5000;

    int m = inf.readInt(1, MAX_MN, "m");
    inf.readSpace();
    int n = inf.readInt(1, MAX_MN, "n");
    inf.readEoln();

    int k = inf.readInt(1, MAX_K, "k");
    inf.readEoln();

    vector<Bus> buses(k + 1); // index by bus id for convenience
    vector<bool> seenId(k + 1, false);

    for (int i = 0; i < k; ++i) {
        int b = inf.readInt(1, k, "b");
        inf.readSpace();
        int x1 = inf.readInt(1, m, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, n, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, m, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, n, "y2");
        inf.readEoln();

        ensuref(!seenId[b], "Bus id %d appears multiple times", b);
        seenId[b] = true;

        ensuref(!(x1 == x2 && y1 == y2),
                "Bus %d has zero-length segment at (%d,%d)", b, x1, y1);

        bool horiz = (y1 == y2);
        bool vert  = (x1 == x2);
        ensuref(horiz || vert,
                "Bus %d segment is not axis-aligned: (%d,%d) to (%d,%d)",
                b, x1, y1, x2, y2);

        // Normalize so that for horizontal: x1 <= x2; for vertical: y1 <= y2
        if (horiz && x1 > x2) swap(x1, x2);
        if (vert  && y1 > y2) swap(y1, y2);

        buses[b] = {b, x1, y1, x2, y2, horiz};
    }

    // Ensure all bus ids 1..k appear exactly once
    for (int id = 1; id <= k; ++id) {
        ensuref(seenId[id], "Bus id %d is missing", id);
    }

    int sx = inf.readInt(1, m, "s_x");
    inf.readSpace();
    int sy = inf.readInt(1, n, "s_y");
    inf.readSpace();
    int dx = inf.readInt(1, m, "d_x");
    inf.readSpace();
    int dy = inf.readInt(1, n, "d_y");
    inf.readEoln();

    ensuref(!(sx == dx && sy == dy),
            "Source and destination must be different, but both are (%d,%d)",
            sx, sy);

    // ---------- Global property: at least one path from source to destination exists ----------

    // Helper lambdas to check if a point lies on a bus
    auto pointOnBus = [](const Bus &bus, int x, int y) -> bool {
        if (bus.horizontal) {
            if (y != bus.y1) return false;
            return bus.x1 <= x && x <= bus.x2;
        } else {
            if (x != bus.x1) return false;
            return bus.y1 <= y && y <= bus.y2;
        }
    };

    // Build adjacency between buses by intersection
    // O(k^2) is fine for k <= 5000 (25M checks)
    vector<vector<int>> adj(k + 1);
    for (int i = 1; i <= k; ++i) {
        for (int j = i + 1; j <= k; ++j) {
            const Bus &a = buses[i];
            const Bus &b = buses[j];
            bool intersect = false;
            if (a.horizontal && b.horizontal) {
                if (a.y1 == b.y1) {
                    if (!(a.x2 < b.x1 || b.x2 < a.x1))
                        intersect = true;
                }
            } else if (!a.horizontal && !b.horizontal) {
                if (a.x1 == b.x1) {
                    if (!(a.y2 < b.y1 || b.y2 < a.y1))
                        intersect = true;
                }
            } else {
                const Bus &h = a.horizontal ? a : b;
                const Bus &v = a.horizontal ? b : a;
                int ix = v.x1;
                int iy = h.y1;
                if (h.x1 <= ix && ix <= h.x2 &&
                    v.y1 <= iy && iy <= v.y2)
                    intersect = true;
            }
            if (intersect) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // Collect buses that contain source or destination
    vector<int> srcBuses, dstBuses;
    srcBuses.reserve(k);
    dstBuses.reserve(k);

    for (int i = 1; i <= k; ++i) {
        if (pointOnBus(buses[i], sx, sy)) srcBuses.push_back(i);
        if (pointOnBus(buses[i], dx, dy)) dstBuses.push_back(i);
    }

    ensuref(!srcBuses.empty(),
            "No bus passes through source point (%d,%d)", sx, sy);
    ensuref(!dstBuses.empty(),
            "No bus passes through destination point (%d,%d)", dx, dy);

    // BFS from any source-bus, find minimal buses needed to reach any dst-bus
    const int INF = (int)1e9;
    vector<int> dist(k + 1, INF);
    queue<int> q;

    for (int id : srcBuses) {
        dist[id] = 1; // taking this bus
        q.push(id);
    }

    int best = INF;
    vector<char> isDst(k + 1, 0);
    for (int id : dstBuses) isDst[id] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (isDst[u]) {
            best = dist[u];
            break; // first time reaching any dst-bus is minimal
        }
        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    ensuref(best != INF,
            "Statement guarantees at least one path, but no path found from (%d,%d) to (%d,%d)",
            sx, sy, dx, dy);

    inf.readEof();
}
