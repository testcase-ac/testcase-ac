#include "testlib.h"
#include <numeric>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    int a = inf.readInt(1, n, "person_a");
    inf.readSpace();
    int b = inf.readInt(1, n, "person_b");
    inf.readEoln();
    ensuref(a != b, "the two people must be different: %d", a);

    int m = inf.readInt(0, n - 1, "m");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    vector<int> dsu(n + 1);
    iota(dsu.begin(), dsu.end(), 0);

    auto findRoot = [&](int x) {
        while (dsu[x] != x) {
            dsu[x] = dsu[dsu[x]];
            x = dsu[x];
        }
        return x;
    };

    set<pair<int, int>> relations;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "parent");
        inf.readSpace();
        int y = inf.readInt(1, n, "child");
        inf.readEoln();

        ensuref(x != y, "person %d cannot be their own parent", x);
        ensuref(parent[y] == 0, "person %d has more than one parent", y);
        ensuref(relations.insert({x, y}).second,
                "duplicate relation at index %d: (%d, %d)", i + 1, x, y);

        int rx = findRoot(x);
        int ry = findRoot(y);
        ensuref(rx != ry, "parent-child relations must not contain a cycle");

        parent[y] = x;
        dsu[ry] = rx;
    }

    inf.readEof();
    return 0;
}
