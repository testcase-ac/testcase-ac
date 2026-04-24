#include "testlib.h"
#include <vector>
#include <set>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of candy shops
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Candy types at each shop
    vector<int> candy = inf.readInts(N, 1, 5, "candy_type");
    inf.readEoln();

    // Prepare union‐find for cycle & connectivity checks
    vector<int> parent(N+1);
    iota(parent.begin(), parent.end(), 0);
    auto findRoot = [&](int x) {
        int r = x;
        while (parent[r] != r) r = parent[r];
        while (parent[x] != r) {
            int p = parent[x];
            parent[x] = r;
            x = p;
        }
        return r;
    };

    // Read edges, check self‐loops, multi‐edges, and cycles
    set<pair<int,int>> seenEdges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!seenEdges.count({a,b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        seenEdges.insert({a,b});

        int ru = findRoot(u), rv = findRoot(v);
        ensuref(ru != rv,
                "Cycle detected at edge index %d: (%d, %d)", i, u, v);
        parent[ru] = rv;
    }

    // Check connectivity: with N‐1 edges and no cycles, this also ensures a tree,
    // but we double‐check components to give clear error if disconnected.
    set<int> comps;
    for (int i = 1; i <= N; i++) {
        comps.insert(findRoot(i));
    }
    ensuref(comps.size() == 1,
            "Graph is not connected: %d components found", (int)comps.size());

    // Number of friends
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Each friend's location and favorite candy type
    for (int i = 0; i < M; i++) {
        inf.readInt(1, N, "friend_store");
        inf.readSpace();
        inf.readInt(1, 5, "friend_candy");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
