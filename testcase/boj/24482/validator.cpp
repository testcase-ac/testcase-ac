#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, R
    int N = inf.readInt(5, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // Read edges, check for u < v, no duplicates
    set<pair<int,int>> edges;
    edges.clear();
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops and enforce u < v
        ensuref(u < v,
                "Invalid edge at index %d: (%d, %d). Expected u < v.", i, u, v);

        // No duplicate edges
        pair<int,int> e = {u, v};
        ensuref(!edges.count(e),
                "Multiple edges detected at index %d: (%d, %d)", i, u, v);

        edges.insert(e);
    }

    inf.readEof();
    return 0;
}
