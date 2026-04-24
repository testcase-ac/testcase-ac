#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

// Simple DSU for 1..n
struct DSU {
    int n;
    vector<int> p, r;
    int comps;
    DSU(int _n): n(_n), p(_n+1), r(_n+1, 0), comps(_n) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    // returns true if merged, false if already in same set
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        comps--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read vertex values c[1..N]
    vector<int> c = inf.readInts(N, 1, N, "c_i");
    inf.readEoln();

    // Check at least one duplicate among c_i
    {
        vector<char> seen(N+1, 0);
        bool has_dup = false;
        for (int i = 0; i < N; i++) {
            if (seen[c[i]]) {
                has_dup = true;
                break;
            }
            seen[c[i]] = 1;
        }
        ensuref(has_dup, "There must be at least two vertices with the same value");
    }

    // Read edges and validate tree properties
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at edge %d: both endpoints are %d", i+1, u);

        // No multiple edges
        pair<int,int> e = u < v ? make_pair(u, v) : make_pair(v, u);
        ensuref(!edges.count(e),
                "Multiple edges detected: (%d, %d)", e.first, e.second);
        edges.insert(e);

        // No cycles
        ensuref(dsu.join(u, v),
                "Cycle detected at edge %d: (%d, %d)", i+1, u, v);
    }

    // Check connectivity (should be exactly 1 component)
    ensuref(dsu.comps == 1,
            "The graph is disconnected: expected a single tree component");

    // End of file
    inf.readEof();
    return 0;
}
