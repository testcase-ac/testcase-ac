#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
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

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    const long long maxTotalFruit = 2147483647LL;
    long long totalFruit = 0;
    for (int i = 1; i <= n; ++i) {
        long long fruit = inf.readLong(0LL, maxTotalFruit, "fruit");
        totalFruit += fruit;
        ensuref(totalFruit <= maxTotalFruit,
                "total fruit count exceeds 2^31-1 after vertex %d", i);

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);
        ensuref(dsu.unite(a, b), "cycle detected at edge %d: %d %d", i, a, b);
    }

    inf.readEof();
}
