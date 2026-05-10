#include "testlib.h"
#include <vector>
#include <tuple>
#include <string>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n, 0) { for(int i = 0; i < n; i++) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read edges
    vector<tuple<int,int,int>> edges;
    edges.reserve(N-1);
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, 10000, "w");
        inf.readEoln();
        ensuref(u != v,
                "Edge %d has same endpoints: (%d, %d)", i+1, u, v);
        edges.emplace_back(u, v, w);
    }

    // Validate tree structure: no cycles and connected
    DSU dsu(N+1);
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        tie(u, v, w) = edges[i];
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge %d: (%d, %d)", i+1, u, v);
    }
    // Check connectivity: all nodes must be in one component
    int root = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root,
                "Tree is disconnected: node %d is not reachable from node 1", i);
    }

    // Read queries
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();
        // queries may ask same node twice; distance is zero, allowed
    }

    // End of file
    inf.readEof();
    return 0;
}
