#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
public:
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

private:
    vector<int> parent;
    vector<int> size;
};

static pair<int, int> readEdge(int n, const char* prefix, int index, set<pair<int, int>>& seen) {
    string sName = format("%s_s_%d", prefix, index);
    string eName = format("%s_e_%d", prefix, index);
    string dName = format("%s_d_%d", prefix, index);

    int s = inf.readInt(1, n, sName);
    inf.readSpace();
    int e = inf.readInt(1, n, eName);
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, dName);
    inf.readEoln();

    ensuref(s != e, "%s edge %d is a self-loop at building %d", prefix, index, s);
    pair<int, int> edge = minmax(s, e);
    ensuref(seen.insert(edge).second, "duplicate %s edge %d between buildings %d and %d", prefix, index, edge.first, edge.second);
    return edge;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "k");
    inf.readSpace();
    int x = inf.readInt(1, 200000, "x");
    inf.readSpace();
    int y = inf.readInt(1, 200000, "y");
    inf.readEoln();

    set<pair<int, int>> sidewalks;
    set<pair<int, int>> roads;
    Dsu dsu(n);

    for (int i = 1; i <= x; ++i) {
        auto edge = readEdge(n, "sidewalk", i, sidewalks);
        dsu.unite(edge.first, edge.second);
    }
    for (int i = 1; i <= y; ++i) {
        auto edge = readEdge(n, "road", i, roads);
        dsu.unite(edge.first, edge.second);
    }

    ensuref(dsu.find(1) == dsu.find(n), "building %d is not reachable from building 1", n);
    inf.readEof();
}
