#include "testlib.h"
#include <vector>
#include <set>
#include <map>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m
    int n = inf.readInt(3, 5000, "n");
    inf.readSpace();
    int m = inf.readInt(3, 10000, "m");
    inf.readEoln();

    // To check duplicate tunnels (undirected)
    set<pair<int,int>> tunnels;
    vector<pair<int,int>> edges; // store endpoints of each tunnel
    vector<int> adj1; // neighbors of node 1

    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 10000, "c_i");
        inf.readSpace();
        int d = inf.readInt(1, 10000, "d_i");
        inf.readEoln();

        ensuref(a != b,
                "Self-loop detected at tunnel index %d: (%d,%d)", i, a, b);
        int u = min(a,b), v = max(a,b);
        pair<int,int> uv = make_pair(u,v);
        ensuref(!tunnels.count(uv),
                "Multiple tunnels between rooms %d and %d at tunnel index %d", u, v, i);
        tunnels.insert(uv);
        edges.push_back(uv);
        if (a == 1) adj1.push_back(b);
        else if (b == 1) adj1.push_back(a);
    }

    // Build DSU over nodes 1..n, but we will ignore node 1 in unions
    DSU dsu(n);
    for (auto &uv : edges) {
        int u = uv.first, v = uv.second;
        if (u != 1 && v != 1) {
            dsu.unite(u, v);
        }
    }

    // We need at least one simple cycle through node 1:
    // i.e., two distinct neighbors of 1 that are connected in the graph excluding node 1.
    ensuref((int)adj1.size() >= 2,
            "Node 1 has fewer than two neighbors, cannot form a cycle");

    map<int,int> comp_count;
    for (int v : adj1) {
        // v in [2..n]
        int c = dsu.find(v);
        comp_count[c]++;
    }
    bool has_cycle = false;
    for (auto &kv : comp_count) {
        if (kv.second >= 2) {
            has_cycle = true;
            break;
        }
    }
    ensuref(has_cycle,
            "No simple cycle through node 1 exists (no two neighbors of 1 are connected elsewhere)");

    inf.readEof();
    return 0;
}
