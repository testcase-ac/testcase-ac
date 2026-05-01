#include "testlib.h"
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N and M: number of vertices and edges
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // We must ensure the graph is simple: no self-loops, no multiple edges,
    // and edges are given with 1 <= u < v <= N as per statement.
    set<pair<int,int>> edges;

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // Enforce 1 <= u < v <= N
        ensuref(u < v,
                "Edge index %d violates constraint 1 <= u_i < v_i <= N (got u=%d, v=%d)",
                i, u, v);

        pair<int,int> e = make_pair(u, v);
        ensuref(!edges.count(e),
                "Multiple edge detected at index %d: (%d, %d) already exists",
                i, u, v);
        edges.insert(e);
    }

    // No extra tokens / whitespace after the last line
    inf.readEof();
}
