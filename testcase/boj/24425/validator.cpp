#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 200000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readSpace();
    inf.readInt(1, 1000000000, "L");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> roads;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n - 1, "A_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "B_i");
        inf.readSpace();
        inf.readInt(1, 2, "C_i");
        inf.readEoln();

        ensuref(roads.insert({a, b}).second,
                "duplicate road at index %d: (%d, %d)", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int town = 2; town <= n; ++town) {
        ensuref(dsu.find(town) == root, "town %d is not connected to town 1", town);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(2, n, "T_j");
        inf.readEoln();
    }

    inf.readEof();
}
