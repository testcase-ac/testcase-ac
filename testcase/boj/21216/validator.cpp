#include "testlib.h"

#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        // CHECK: The statement says each line is a pair of readers, so a reader paired with herself is rejected.
        ensuref(i != j, "self-loop at edge %d: %d %d", edgeIndex, i, j);

        pair<int, int> edge = minmax(i, j);
        // CHECK: M counts pairs of readers, so repeated undirected pairs are rejected.
        ensuref(edges.insert(edge).second,
                "duplicate pair at edge %d: %d %d", edgeIndex, i, j);
    }

    inf.readEof();
}
