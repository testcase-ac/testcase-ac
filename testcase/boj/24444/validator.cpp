#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N, M, R
    int N = inf.readInt(5, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // Validate edges: undirected, no loops, no duplicates, u < v
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // Problem guarantees 1 ≤ u < v ≤ N, u != v
        ensuref(u < v,
                "Edge ordering violated at edge index %d: u (%d) >= v (%d)", 
                i, u, v);

        pair<int,int> e = make_pair(u, v);
        ensuref(!edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)",
                i, u, v);
        edges.insert(e);
    }

    inf.readEof();
    return 0;
}
