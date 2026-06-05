#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int degree = inf.readInt(0, m, "degree");
        set<int> seen;
        for (int j = 1; j <= degree; ++j) {
            inf.readSpace();
            int b = inf.readInt(1, m, "B_j");
            // CHECK: The statement describes an ordinary bipartite graph, not a multigraph.
            ensuref(seen.insert(b).second,
                    "duplicate B vertex %d in adjacency list for A vertex %d",
                    b,
                    i);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
