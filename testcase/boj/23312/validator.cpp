#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

struct LinkCutTree {
    struct Node {
        int child[2] = {0, 0};
        int parent = 0;
        bool reversed = false;
    };

    vector<Node> tree;

    explicit LinkCutTree(int n) : tree(n + 1) {}

    bool isRoot(int x) const {
        int p = tree[x].parent;
        return p == 0 || (tree[p].child[0] != x && tree[p].child[1] != x);
    }

    void push(int x) {
        if (!tree[x].reversed) {
            return;
        }
        swap(tree[x].child[0], tree[x].child[1]);
        for (int c : tree[x].child) {
            if (c != 0) {
                tree[c].reversed = !tree[c].reversed;
            }
        }
        tree[x].reversed = false;
    }

    void pushPath(int x) {
        if (!isRoot(x)) {
            pushPath(tree[x].parent);
        }
        push(x);
    }

    void rotate(int x) {
        int p = tree[x].parent;
        int g = tree[p].parent;
        int side = tree[p].child[1] == x;
        int b = tree[x].child[side ^ 1];

        if (!isRoot(p)) {
            tree[g].child[tree[g].child[1] == p] = x;
        }
        tree[x].parent = g;

        tree[x].child[side ^ 1] = p;
        tree[p].parent = x;

        tree[p].child[side] = b;
        if (b != 0) {
            tree[b].parent = p;
        }
    }

    void splay(int x) {
        pushPath(x);
        while (!isRoot(x)) {
            int p = tree[x].parent;
            int g = tree[p].parent;
            if (!isRoot(p)) {
                bool zigzig = (tree[p].child[0] == x) == (tree[g].child[0] == p);
                rotate(zigzig ? p : x);
            }
            rotate(x);
        }
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y != 0; y = tree[y].parent) {
            splay(y);
            tree[y].child[1] = last;
            last = y;
        }
        splay(x);
    }

    void makeRoot(int x) {
        access(x);
        tree[x].reversed = !tree[x].reversed;
    }

    int findRoot(int x) {
        access(x);
        while (true) {
            push(x);
            if (tree[x].child[0] == 0) {
                break;
            }
            x = tree[x].child[0];
        }
        splay(x);
        return x;
    }

    bool connected(int a, int b) {
        if (a == b) {
            return true;
        }
        return findRoot(a) == findRoot(b);
    }

    void link(int a, int b) {
        makeRoot(a);
        tree[a].parent = b;
    }

    void cut(int a, int b) {
        makeRoot(a);
        access(b);
        ensuref(tree[b].child[0] == a && tree[a].child[1] == 0,
                "internal error: attempted to cut a non-tree edge (%d, %d)", a, b);
        tree[b].child[0] = 0;
        tree[a].parent = 0;
    }
};

long long edgeKey(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return (static_cast<long long>(a) << 20) | b;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 193 * 193, "N");
    inf.readEoln();

    vector<int> firstCity(n + 1), lastCity(n + 1);
    vector<pair<int, int>> initialEdges;
    vector<pair<int, int>> countryRanges;

    long long totalCities = 0;
    long long totalInitialEdges = 0;

    for (int country = 1; country <= n; ++country) {
        int v = inf.readInt(1, 1000000, "V_i");
        inf.readSpace();
        int e = inf.readInt(0, v - 1, "E_i");
        inf.readEoln();

        ensuref(totalCities + v <= 1000000,
                "sum V exceeds 1000000 after country %d", country);

        firstCity[country] = static_cast<int>(totalCities) + 1;
        totalCities += v;
        lastCity[country] = static_cast<int>(totalCities);
        totalInitialEdges += e;

        countryRanges.push_back({firstCity[country], lastCity[country]});

        vector<int> parent(v + 1);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        unordered_set<long long> countryEdges;
        countryEdges.reserve(static_cast<size_t>(e) * 2 + 1);

        for (int j = 1; j <= e; ++j) {
            int u = inf.readInt(firstCity[country], lastCity[country], "u");
            inf.readSpace();
            int vtx = inf.readInt(firstCity[country], lastCity[country], "v");
            inf.readEoln();

            ensuref(u != vtx, "initial road %d of country %d is a self-loop", j, country);
            long long key = edgeKey(u, vtx);
            ensuref(countryEdges.insert(key).second,
                    "duplicate initial road in country %d: (%d, %d)", country, u, vtx);

            int ru = find(u - firstCity[country] + 1);
            int rv = find(vtx - firstCity[country] + 1);
            ensuref(ru != rv,
                    "initial roads in country %d contain a cycle at edge %d", country, j);
            parent[ru] = rv;

            initialEdges.push_back({u, vtx});
        }
    }

    ensuref(n <= totalCities, "N must be at most sum V");

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    LinkCutTree forest(static_cast<int>(totalCities));
    unordered_set<long long> activeEdges;
    activeEdges.reserve(static_cast<size_t>(totalInitialEdges + q) * 2 + 1);

    for (auto [u, v] : initialEdges) {
        activeEdges.insert(edgeKey(u, v));
        forest.link(u, v);
    }

    bool hasPrintQuery = false;

    for (int query = 1; query <= q; ++query) {
        int type = inf.readInt(1, 3, "query_type");

        if (type == 1) {
            inf.readSpace();
            int k = inf.readInt(1, n, "k");
            inf.readEoln();
            (void)k;
            hasPrintQuery = true;
            continue;
        }

        inf.readSpace();
        int u = inf.readInt(1, static_cast<int>(totalCities), "u");
        inf.readSpace();
        int v = inf.readInt(1, static_cast<int>(totalCities), "v");
        inf.readEoln();

        ensuref(u != v, "query %d uses the same city twice: %d", query, u);

        int cu = upper_bound(countryRanges.begin(), countryRanges.end(), make_pair(u, 1000001))
                 - countryRanges.begin();
        int cv = upper_bound(countryRanges.begin(), countryRanges.end(), make_pair(v, 1000001))
                 - countryRanges.begin();
        ensuref(cu == cv, "query %d connects cities from different countries: %d %d", query, u, v);

        long long key = edgeKey(u, v);
        bool edgeExists = activeEdges.find(key) != activeEdges.end();

        if (type == 2) {
            ensuref(edgeExists, "query %d deletes a road that does not exist: (%d, %d)",
                    query, u, v);
            activeEdges.erase(key);
            forest.cut(u, v);
        } else {
            ensuref(!edgeExists, "query %d adds a road that already exists: (%d, %d)",
                    query, u, v);
            ensuref(!forest.connected(u, v),
                    "query %d adds a road inside one existing island: (%d, %d)", query, u, v);
            activeEdges.insert(key);
            forest.link(u, v);
        }
    }

    ensuref(hasPrintQuery, "at least one type-1 query is required");
    inf.readEof();
}
