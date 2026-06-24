#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int n, m;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int size) : parent(size) {
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

void readTree(InStream& stream) {
    vector<int> degree(n, 0);
    set<pair<int, int>> edges;
    Dsu dsu(n);

    for (int i = 0; i < n - 1; ++i) {
        int u = stream.readInt(0, n - 1, format("edge[%d].u", i + 1).c_str());
        int v = stream.readInt(0, n - 1, format("edge[%d].v", i + 1).c_str());
        stream.readEoln();

        if (u == v) {
            stream.quitf(_wa, "edge %d is a self-loop on vertex %d", i + 1, u);
        }

        pair<int, int> edge = minmax(u, v);
        if (!edges.insert(edge).second) {
            stream.quitf(_wa, "edge %d repeats edge %d %d", i + 1, edge.first, edge.second);
        }

        if (!dsu.unite(u, v)) {
            stream.quitf(_wa, "edge %d creates a cycle", i + 1);
        }

        ++degree[u];
        ++degree[v];
    }

    stream.readEof();

    int root = dsu.find(0);
    for (int vertex = 1; vertex < n; ++vertex) {
        if (dsu.find(vertex) != root) {
            stream.quitf(_wa, "graph is disconnected; vertex %d is unreachable from 0", vertex);
        }
    }

    int leaves = 0;
    for (int vertex = 0; vertex < n; ++vertex) {
        if (degree[vertex] == 1) {
            ++leaves;
        }
    }
    if (leaves != m) {
        stream.quitf(_wa, "expected %d leaves, found %d", m, leaves);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    readTree(ans);
    readTree(ouf);

    quitf(_ok, "valid tree with %d leaves", m);
}
