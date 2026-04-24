#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of attendees
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Number of acquaintance relations
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // Read edges and check for loops or duplicates
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        // Read two endpoints in [1, N]
        vector<int> ab = inf.readInts(2, 1, N, "edge");
        inf.readEoln();

        int a = ab[0], b = ab[1];
        // No self-loop
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);

        // No multiple edges (undirected)
        int u = min(a, b), v = max(a, b);
        pair<int,int> p = make_pair(u, v);
        ensuref(!edges.count(p),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert(p);
    }

    inf.readEof();
    return 0;
}
