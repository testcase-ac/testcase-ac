#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = findRoot(parent, parent[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        inf.readInt(1, 100, "C_i");
        inf.readEoln();

        ensuref(a < b, "edge %d endpoints must satisfy A_i < B_i, got %d %d", i, a, b);

        // CHECK: the statement does not explicitly forbid parallel roads, so
        // duplicate city pairs are accepted.
        int rootA = findRoot(parent, a);
        int rootB = findRoot(parent, b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }

    int root = findRoot(parent, 1);
    for (int city = 2; city <= n; ++city) {
        ensuref(findRoot(parent, city) == root, "graph is not connected; city %d is unreachable from city 1", city);
    }

    inf.readEof();
}
