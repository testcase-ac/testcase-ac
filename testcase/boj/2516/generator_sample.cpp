#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

bool addEdge(vector<set<int>>& adj, int u, int v) {
    if (u == v || adj[u].count(v) || adj[u].size() >= 3 || adj[v].size() >= 3) {
        return false;
    }
    adj[u].insert(v);
    adj[v].insert(u);
    return true;
}

void addPath(vector<set<int>>& adj, const vector<int>& nodes) {
    for (int i = 1; i < int(nodes.size()); ++i) {
        addEdge(adj, nodes[i - 1], nodes[i]);
    }
}

void addCycle(vector<set<int>>& adj, const vector<int>& nodes) {
    addPath(adj, nodes);
    if (nodes.size() > 2) {
        addEdge(adj, nodes.back(), nodes.front());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 16);
    vector<set<int>> adj(n + 1);

    vector<int> nodes;
    for (int i = 1; i <= n; ++i) {
        nodes.push_back(i);
    }
    shuffle(nodes.begin(), nodes.end());

    if (mode == 0) {
        int target = rnd.next(0, n);
        vector<pair<int, int>> edges;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                edges.emplace_back(i, j);
            }
        }
        shuffle(edges.begin(), edges.end());
        for (auto [u, v] : edges) {
            if (target == 0) {
                break;
            }
            if (addEdge(adj, u, v)) {
                --target;
            }
        }
    } else if (mode == 1) {
        addPath(adj, nodes);
        int extra = rnd.next(0, n / 2);
        while (extra--) {
            addEdge(adj, rnd.any(nodes), rnd.any(nodes));
        }
    } else if (mode == 2) {
        addCycle(adj, nodes);
        int extra = rnd.next(0, n / 3);
        while (extra--) {
            addEdge(adj, rnd.any(nodes), rnd.any(nodes));
        }
    } else if (mode == 3) {
        for (int i = 0; i + 2 < n; i += 3) {
            addEdge(adj, nodes[i], nodes[i + 1]);
            addEdge(adj, nodes[i + 1], nodes[i + 2]);
            addEdge(adj, nodes[i + 2], nodes[i]);
        }
        int extra = rnd.next(0, n / 2);
        while (extra--) {
            addEdge(adj, rnd.any(nodes), rnd.any(nodes));
        }
    } else {
        vector<int> left, right;
        for (int i = 0; i < n; ++i) {
            (i % 2 == 0 ? left : right).push_back(nodes[i]);
        }
        vector<pair<int, int>> edges;
        for (int u : left) {
            for (int v : right) {
                edges.emplace_back(u, v);
            }
        }
        shuffle(edges.begin(), edges.end());
        int target = rnd.next(n - 2, min<int>(edges.size(), 3 * n / 2));
        for (auto [u, v] : edges) {
            if (target == 0) {
                break;
            }
            if (addEdge(adj, u, v)) {
                --target;
            }
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        printf("%d", int(adj[i].size()));
        for (int v : adj[i]) {
            printf(" %d", v);
        }
        printf("\n");
    }

    return 0;
}
