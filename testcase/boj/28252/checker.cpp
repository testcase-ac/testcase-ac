#include "testlib.h"

#include <numeric>
#include <queue>
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

int n;
vector<int> target;
int total_vertices;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    int m = stream.readInt(-1, total_vertices, "M");
    if (m == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    if (m != total_vertices) {
        stream.quitf(_wa, "M must be sum(A_i): expected %d, found %d", total_vertices, m);
    }

    vector<vector<int>> graph(m + 1);
    Dsu dsu(m);
    set<pair<int, int>> edges;

    for (int i = 0; i < m - 1; ++i) {
        int u = stream.readInt(1, m, format("edge[%d].u", i + 1).c_str());
        int v = stream.readInt(1, m, format("edge[%d].v", i + 1).c_str());
        if (u == v) {
            stream.quitf(_wa, "edge %d is a self-loop at vertex %d", i + 1, u);
        }
        pair<int, int> edge = minmax(u, v);
        if (!edges.insert(edge).second) {
            stream.quitf(_wa, "edge %d duplicates (%d, %d)", i + 1, edge.first, edge.second);
        }
        if (!dsu.unite(u, v)) {
            stream.quitf(_wa, "edge %d creates a cycle", i + 1);
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after edge list");
    }

    if (m >= 1) {
        int root = dsu.find(1);
        for (int v = 2; v <= m; ++v) {
            if (dsu.find(v) != root) {
                stream.quitf(_wa, "output graph is disconnected at vertex %d", v);
            }
        }
    }

    vector<int> degree(m + 1);
    vector<char> removed(m + 1, false);
    queue<int> leaves;
    for (int v = 1; v <= m; ++v) {
        degree[v] = static_cast<int>(graph[v].size());
        if (degree[v] <= 1) {
            leaves.push(v);
        }
    }

    int removed_count = 0;
    for (int round = 0; round < n; ++round) {
        int count = static_cast<int>(leaves.size());
        if (count != target[round]) {
            stream.quitf(_wa, "round %d removes %d vertices, expected %d", round + 1, count, target[round]);
        }

        vector<int> current;
        current.reserve(count);
        while (!leaves.empty()) {
            int v = leaves.front();
            leaves.pop();
            if (!removed[v]) {
                current.push_back(v);
            }
        }

        for (int v : current) {
            removed[v] = true;
            ++removed_count;
        }

        for (int v : current) {
            for (int to : graph[v]) {
                if (removed[to]) {
                    continue;
                }
                --degree[to];
                if (degree[to] == 1) {
                    leaves.push(to);
                }
            }
        }
    }

    if (removed_count != m) {
        stream.quitf(_wa, "tree has %d vertices remaining after %d rounds", m - removed_count, n);
    }
    if (!leaves.empty()) {
        stream.quitf(_wa, "tree has extra leaf-removal rounds after the target sequence");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    target.resize(n);
    total_vertices = 0;
    for (int i = 0; i < n; ++i) {
        target[i] = inf.readInt();
        total_vertices += target[i];
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "jury reports impossible, but participant provided a valid tree");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury provided a valid tree");
    }

    quitf(_ok, "participant provided a valid tree with leaf sequence A");
}
