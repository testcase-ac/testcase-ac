#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000, "energy_i");
        inf.readEoln();
    }

    DisjointSet dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);
        ensuref(dsu.unite(a, b), "cycle formed at edge %d: %d %d", i, a, b);
    }

    for (int room = 2; room <= n; ++room) {
        ensuref(dsu.find(1) == dsu.find(room), "room %d is not connected to room 1", room);
    }

    inf.readEof();
}
