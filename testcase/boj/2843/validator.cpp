#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of vertices
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Initial outgoing edges: for each vertex, 0 means none, otherwise destination in [1, N]
    vector<int> nxt = inf.readInts(N, 0, N, "nxt");
    inf.readEoln();

    // Number of queries
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // We'll track current outgoing edge for each vertex to validate type-2 queries
    vector<int> cur = nxt;

    for (int i = 0; i < Q; i++) {
        // Read query type and vertex X
        char buf1[32], buf2[32];
        sprintf(buf1, "type_%d", i+1);
        sprintf(buf2, "X_%d", i+1);
        int type = inf.readInt(1, 2, buf1);
        inf.readSpace();
        int X = inf.readInt(1, N, buf2);
        inf.readEoln();

        // For type-2, ensure there's an outgoing edge to remove
        if (type == 2) {
            ensuref(cur[X-1] != 0,
                    "Query %d: cannot remove outgoing edge from vertex %d because it has none",
                    i+1, X);
            cur[X-1] = 0;
        }
    }

    inf.readEof();
    return 0;
}
