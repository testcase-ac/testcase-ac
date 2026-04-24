#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 4000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Check edges: undirected, no loops, no multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int d = inf.readInt(1, 100000, "d");
        inf.readEoln();

        // No loops
        ensuref(a != b, "Loop detected at edge %d: %d %d", i+1, a, b);

        // No multiple edges
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}),
                "Multiple edges detected between %d and %d at edge %d", u, v, i+1);
        edges.insert({u, v});
    }

    // File must end right here
    inf.readEof();
    return 0;
}
