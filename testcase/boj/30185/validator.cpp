#include "testlib.h"
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read fruit string
    string s = inf.readToken("[AB]+", "s");
    ensuref((int)s.size() == N,
            "The length of string s must be %d, but got %d", N, (int)s.size());
    inf.readEoln();

    // Prepare DSU for connectivity check
    vector<int> parent(N+1);
    for (int i = 1; i <= N; i++) parent[i] = i;
    function<int(int)> findp = [&](int x) {
        return parent[x] == x ? x : parent[x] = findp(parent[x]);
    };
    auto unite = [&](int a, int b) {
        a = findp(a); b = findp(b);
        if (a != b) parent[a] = b;
    };

    // Read edges, check loops and multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d, %d)", i, u, v);
        pair<int,int> p = u < v ? make_pair(u, v) : make_pair(v, u);
        ensuref(!edges.count(p),
                "Multiple edges detected at edge %d: (%d, %d)", i, u, v);
        edges.insert(p);

        unite(u, v);
    }

    // Check connectivity: all nodes must be in one component
    if (N >= 1) {
        int root1 = findp(1);
        for (int i = 2; i <= N; i++) {
            ensuref(findp(i) == root1,
                    "The graph is not connected: node %d is not reachable from node 1", i);
        }
    }

    inf.readEof();
    return 0;
}
