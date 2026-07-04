#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 1000, "N");
        inf.readEoln();

        vector<int> parent(n + 1);
        iota(parent.begin(), parent.end(), 0);

        for (int i = 1; i <= n - 1; ++i) {
            int a = inf.readInt(1, n, "A_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "B_i");
            inf.readSpace();
            inf.readLong(1LL, 1000000000LL, "C_i");
            inf.readEoln();

            ensuref(a < b, "edge %d has A_i >= B_i: %d >= %d", i, a, b);

            int rootA = findRoot(parent, a);
            int rootB = findRoot(parent, b);
            ensuref(rootA != rootB, "edge %d creates a cycle: %d %d", i, a, b);
            parent[rootA] = rootB;
        }

        int root = findRoot(parent, 1);
        for (int v = 2; v <= n; ++v) {
            ensuref(findRoot(parent, v) == root, "sight %d is disconnected", v);
        }
    }

    inf.readEof();
}
