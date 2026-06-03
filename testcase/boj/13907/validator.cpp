#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 30000, "M");
    inf.readSpace();
    int k = inf.readInt(0, 30000, "K");
    inf.readEoln();

    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int d = inf.readInt(1, n, "D");
    inf.readEoln();
    ensuref(s != d, "S and D must be distinct: %d", s);

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int w = inf.readInt(1, 1000, "w");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy a < b, got %d %d", i, a, b);

        int ra = findRoot(parent, a);
        int rb = findRoot(parent, b);
        if (ra != rb) parent[rb] = ra;
    }

    ensuref(findRoot(parent, s) == findRoot(parent, d),
            "S and D must be connected");

    for (int i = 1; i <= k; ++i) {
        inf.readInt(1, 10, "p");
        inf.readEoln();
    }

    inf.readEof();
}
