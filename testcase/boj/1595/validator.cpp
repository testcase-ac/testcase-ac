#include "testlib.h"

#include <numeric>
#include <set>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
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
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_CITY = 10000;
    // CHECK: The statement only says road lengths are positive integers; cap them
    // at 1e9 as a practical integer-token bound.
    constexpr int MAX_LENGTH = 1000000000;

    Dsu dsu(MAX_CITY);
    set<int> cities;
    set<pair<int, int>> edges;
    int edgeCount = 0;

    while (!inf.eof()) {
        int u = inf.readInt(1, MAX_CITY, "u");
        inf.readSpace();
        int v = inf.readInt(1, MAX_CITY, "v");
        inf.readSpace();
        inf.readInt(1, MAX_LENGTH, "length");
        inf.readEoln();

        ensuref(u != v, "road %d connects city %d to itself", edgeCount + 1, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate road at line %d between %d and %d",
                edgeCount + 1,
                edge.first,
                edge.second);
        ensuref(dsu.unite(u, v),
                "roads contain a cycle at line %d between %d and %d",
                edgeCount + 1,
                u,
                v);

        cities.insert(u);
        cities.insert(v);
        ++edgeCount;
    }

    ensuref(edgeCount > 0, "input must contain at least one road");
    ensuref(edgeCount == static_cast<int>(cities.size()) - 1,
            "expected a tree over the mentioned cities, got %d roads and %d cities",
            edgeCount,
            static_cast<int>(cities.size()));

    int root = dsu.find(*cities.begin());
    for (int city : cities) {
        ensuref(dsu.find(city) == root, "city %d is not connected to the first city", city);
    }

    inf.readEof();
}
