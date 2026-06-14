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

void unite(vector<int>& parent, int a, int b) {
    a = findRoot(parent, a);
    b = findRoot(parent, b);
    if (a != b) {
        parent[b] = a;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 100, "c");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
        // CHECK: The statement calls this an undirected graph but does not forbid parallel edges.
        unite(parent, a, b);
    }

    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    ensuref(s != t, "s and t must be different: %d", s);
    ensuref(findRoot(parent, s) == findRoot(parent, t),
            "s and t must be connected initially: %d %d", s, t);

    inf.readEof();
}
