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

    // Read edges, check no loops, no multiple edges, u < v
    set<pair<int,int>> edges;
    edges.clear();
    for (int i = 1; i <= M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No loops and u < v as per problem
        ensuref(u < v, "Edge %d has u >= v: (%d, %d)", i, u, v);

        // No multiple edges
        pair<int,int> e = {u, v};
        ensuref(!edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        edges.insert(e);
    }

    inf.readEof();
    return 0;
}
