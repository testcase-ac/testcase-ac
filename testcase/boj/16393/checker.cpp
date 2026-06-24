#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int n;
vector<vector<int>> dist_matrix;

struct DSU {
    vector<int> parent;

    explicit DSU(int size) : parent(size) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
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

struct Answer {
    vector<vector<pair<int, int>>> tree;
};

Answer readAnswer(InStream& stream) {
    vector<vector<pair<int, int>>> tree(n);
    DSU dsu(n);

    for (int i = 0; i < n - 1; ++i) {
        int u = stream.readInt(1, n, format("edge[%d].u", i + 1).c_str()) - 1;
        stream.readSpace();
        int v = stream.readInt(1, n, format("edge[%d].v", i + 1).c_str()) - 1;
        stream.readEoln();

        if (u == v) {
            stream.quitf(_wa, "edge %d is a self-loop at vertex %d", i + 1, u + 1);
        }
        if (!dsu.unite(u, v)) {
            stream.quitf(_wa, "edge %d creates a cycle between %d and %d", i + 1, u + 1, v + 1);
        }

        int weight = dist_matrix[u][v];
        tree[u].push_back({v, weight});
        tree[v].push_back({u, weight});
    }

    stream.readEof();

    int root = dsu.find(0);
    for (int v = 1; v < n; ++v) {
        if (dsu.find(v) != root) {
            stream.quitf(_wa, "output graph is not connected");
        }
    }

    vector<long long> tree_dist(n);
    vector<pair<int, int>> stack;

    for (int start = 0; start < n; ++start) {
        fill(tree_dist.begin(), tree_dist.end(), -1);
        tree_dist[start] = 0;
        stack.clear();
        stack.push_back({start, -1});

        while (!stack.empty()) {
            auto [v, parent] = stack.back();
            stack.pop_back();

            for (auto [to, weight] : tree[v]) {
                if (to == parent) {
                    continue;
                }
                tree_dist[to] = tree_dist[v] + weight;
                stack.push_back({to, v});
            }
        }

        for (int v = 0; v < n; ++v) {
            if (tree_dist[v] != dist_matrix[start][v]) {
                stream.quitf(_wa,
                             "tree distance between %d and %d is %lld, expected %d",
                             start + 1,
                             v + 1,
                             tree_dist[v],
                             dist_matrix[start][v]);
            }
        }
    }

    return {tree};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    dist_matrix.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist_matrix[i][j] = inf.readInt();
        }
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid tree");
}
