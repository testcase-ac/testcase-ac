#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N, M, R
    int n = inf.readInt(5, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int r = inf.readInt(1, n, "R");
    inf.readEoln();

    // Read and validate edges: no loops, no duplicates, u < v
    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u < v,
                "Edge %d: u (%d) must be strictly less than v (%d)", 
                i, u, v);
        pair<int,int> e = {u, v};
        ensuref(edges.insert(e).second,
                "Multiple edges detected at edge index %d: (%d, %d)", 
                i, u, v);
    }

    inf.readEof();
    return 0;
}
