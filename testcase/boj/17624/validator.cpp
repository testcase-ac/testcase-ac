#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    int b = inf.readInt(0, n, "b");
    inf.readEoln();

    vector<bool> hasStone(n + 1);
    for (int i = 0; i < b; ++i) {
        if (i > 0) inf.readSpace();
        int x = inf.readInt(1, n, "x_i");
        ensuref(!hasStone[x], "black-stone vertex %d is repeated", x);
        hasStone[x] = true;
    }
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };

    for (int e = 1; e < n; ++e) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        int ru = find(u);
        int rv = find(v);
        ensuref(ru != rv, "edge %d creates a cycle", e);
        parent[ru] = rv;
    }

    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();
    for (int k = 1; k <= q; ++k) {
        setTestCase(k);
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        inf.readInt(0, min(i, b), "j");
        inf.readEoln();
    }

    inf.readEof();
}
