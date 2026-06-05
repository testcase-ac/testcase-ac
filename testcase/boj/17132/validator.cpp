#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = findRoot(parent, parent[x]);
    return parent[x];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        inf.readInt(1, 200, "w");
        inf.readEoln();

        ensuref(x != y, "loop at edge %d: %d %d", i, x, y);
        int rx = findRoot(parent, x);
        int ry = findRoot(parent, y);
        ensuref(rx != ry, "cycle or duplicate edge at edge %d: %d %d", i, x, y);
        parent[ry] = rx;
    }

    inf.readEof();
}
