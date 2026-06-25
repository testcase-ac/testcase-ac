#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    inf.readInt(1, 1000000, "e");
    inf.readEoln();

    set<int> qualities;
    vector<set<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int q = inf.readInt(1, 1000000, "q");
        ensuref(qualities.insert(q).second,
                "quality values must be distinct, duplicate %d at patch %d", q, i);

        inf.readSpace();
        int d = inf.readInt(0, 10, "d");
        for (int j = 0; j < d; ++j) {
            inf.readSpace();
            int neighbor = inf.readInt(1, n, "neighbor");
            ensuref(neighbor != i, "patch %d lists itself as a neighbor", i);
            ensuref(adj[i].insert(neighbor).second,
                    "patch %d lists neighbor %d more than once", i, neighbor);
        }
        inf.readEoln();
    }

    for (int i = 1; i <= n; ++i) {
        for (int neighbor : adj[i]) {
            ensuref(adj[neighbor].count(i),
                    "bi-directional path missing reverse edge %d -> %d", neighbor, i);
        }
    }

    inf.readEof();
}
