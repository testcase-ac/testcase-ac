#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, V, E
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int V = inf.readInt(1, 1000, "V");
    inf.readSpace();
    int E = inf.readInt(0, 10000, "E");
    inf.readEoln();

    // 2. Read A, B
    int A = inf.readInt(1, V, "A");
    inf.readSpace();
    int B = inf.readInt(1, V, "B");
    inf.readEoln();

    // 3. Read H_i
    vector<int> H(N);
    set<int> house_set;
    for (int i = 0; i < N; ++i) {
        H[i] = inf.readInt(1, V, "H_i");
        if (i + 1 < N) inf.readSpace();
        house_set.insert(H[i]);
    }
    inf.readEoln();

    // 4. Read E edges, check for valid constraints
    // - No self-loops (a != b)
    // - No multiple edges between same pair (undirected)
    // - 1 <= a, b <= V
    // - 1 <= l <= 100
    set<pair<int,int>> edge_set;
    vector<vector<pair<int,int>>> adj(V+1); // 1-based

    for (int i = 0; i < E; ++i) {
        int a = inf.readInt(1, V, "a");
        inf.readSpace();
        int b = inf.readInt(1, V, "b");
        inf.readSpace();
        int l = inf.readInt(1, 100, "l");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);
        int u = min(a, b), v = max(a, b);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected between %d and %d at edge %d", a, b, i+1);
        edge_set.insert({u, v});

        adj[a].emplace_back(b, l);
        adj[b].emplace_back(a, l);
    }

    inf.readEof();
}
