#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(2, 40000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 40000, "k");
    inf.readEoln();

    // For edge existence tracking
    set<pair<int,int>> edges;

    for (int i = 0; i < k; ++i) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        int u = inf.readInt(0, n-1, "u");
        inf.readSpace();
        int v = inf.readInt(0, n-1, "v");
        inf.readEoln();

        ensuref(u < v, "On line %d: u (%d) must be less than v (%d)", i+2, u, v);
        // (i+2) because line 1 is n k, then i-th line is line i+2

        if (type == 1) {
            // Build edge
            ensuref(edges.count({u,v}) == 0, "On line %d: Edge (%d,%d) already exists, cannot build again", i+2, u, v);
            edges.insert({u,v});
        } else if (type == 2) {
            // Destroy edge
            ensuref(edges.count({u,v}) == 1, "On line %d: Edge (%d,%d) does not exist, cannot destroy", i+2, u, v);
            edges.erase({u,v});
        } else if (type == 3) {
            // Query: nothing to check
        } else {
            // Should not happen due to readInt(1,3)
            ensuref(false, "On line %d: Invalid type %d", i+2, type);
        }
    }

    inf.readEof();
}
