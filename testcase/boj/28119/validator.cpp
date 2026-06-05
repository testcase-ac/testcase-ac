#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 5000, "M");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };

    auto unite = [&](int a, int b) {
        int ra = findRoot(a);
        int rb = findRoot(b);
        if (ra != rb) {
            parent[rb] = ra;
        }
    };

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(u + 1, n, "v_i");
        inf.readSpace();
        inf.readInt(1, 5000, "w_i");
        inf.readEoln();

        unite(u, v);
    }

    int root = findRoot(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(findRoot(i) == root, "graph is disconnected: vertex %d is not connected to vertex 1", i);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "A_i");
        ensuref(!seen[a], "A is not a permutation: value %d appears more than once", a);
        seen[a] = true;
    }
    inf.readEoln();

    inf.readEof();
}
