#include "testlib.h"

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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(a, n, "b");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: (%d, %d)", i, a, b);
        ensuref(edges.insert({a, b}).second, "duplicate edge at edge %d: (%d, %d)", i, a, b);
        ensuref(dsu.unite(a, b), "cycle formed at edge %d: (%d, %d)", i, a, b);
    }

    for (int town = 2; town <= n; ++town) {
        ensuref(dsu.find(town) == dsu.find(1), "town %d is not connected to town 1", town);
    }

    inf.readEof();
}
