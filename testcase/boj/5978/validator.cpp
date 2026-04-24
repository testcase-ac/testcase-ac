#include "testlib.h"
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of towns N and number of paths M
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Validate each edge: no loops, no duplicate edges (undirected)
    set<pair<int,int>> edges;
    for (int i = 1; i <= M; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();

        // No loops allowed
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);

        // Normalize undirected edge and check duplicates
        int u = min(a, b);
        int v = max(a, b);
        ensuref(!edges.count({u, v}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({u, v});
    }

    // No extra content after last line
    inf.readEof();
    return 0;
}
