#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int p = inf.readInt(2, 800, "P");
    inf.readSpace();
    int c = inf.readInt(1, 1450, "C");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, p, "cow_pasture");
        inf.readEoln();
    }

    vector<int> parent(p + 1);
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

    set<pair<int, int>> edges;
    for (int i = 0; i < c; ++i) {
        int a = inf.readInt(1, p, "path_a");
        inf.readSpace();
        int b = inf.readInt(1, p, "path_b");
        inf.readSpace();
        int len = inf.readInt(1, 225, "path_length");
        (void)len;
        inf.readEoln();

        ensuref(a != b, "path %d is a self-loop at pasture %d", i + 1, a);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate path %d between pastures %d and %d", i + 1, edge.first, edge.second);
        unite(a, b);
    }

    int root = findRoot(1);
    for (int pasture = 2; pasture <= p; ++pasture) {
        ensuref(findRoot(pasture) == root, "pasture graph is disconnected at pasture %d", pasture);
    }

    inf.readEof();
}
