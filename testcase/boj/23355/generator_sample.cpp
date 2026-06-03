#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> buildGraph(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

bool dfsPath(int node, int parent, int target, const vector<vector<int>>& graph, vector<int>& path) {
    path.push_back(node);
    if (node == target) {
        return true;
    }
    for (int next : graph[node]) {
        if (next != parent && dfsPath(next, node, target, graph, path)) {
            return true;
        }
    }
    path.pop_back();
    return false;
}

vector<int> findPath(int from, int to, const vector<vector<int>>& graph) {
    vector<int> path;
    dfsPath(from, 0, to, graph, path);
    return path;
}

int randomNodeOutsidePath(int n, const vector<int>& path) {
    vector<bool> onPath(n + 1, false);
    for (int node : path) {
        onPath[node] = true;
    }
    vector<int> candidates;
    for (int node = 1; node <= n; ++node) {
        if (!onPath[node]) {
            candidates.push_back(node);
        }
    }
    return candidates.empty() ? rnd.any(path) : rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int node = 2; node <= n; ++node) {
            edges.emplace_back(node - 1, node);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int node = 1; node <= n; ++node) {
            if (node != center) {
                edges.emplace_back(center, node);
            }
        }
    } else if (mode == 2) {
        for (int node = 2; node <= n; ++node) {
            int parent = node <= n / 2 + 1 ? 1 : rnd.next(2, node - 1);
            edges.emplace_back(parent, node);
        }
    } else {
        for (int node = 2; node <= n; ++node) {
            int parent = rnd.next(1, node - 1);
            edges.emplace_back(parent, node);
        }
    }

    shuffle(edges.begin(), edges.end());
    vector<int> label(n + 1);
    vector<int> perm;
    for (int node = 1; node <= n; ++node) {
        perm.push_back(node);
    }
    shuffle(perm.begin(), perm.end());
    for (int node = 1; node <= n; ++node) {
        label[node] = perm[node - 1];
    }
    for (auto& [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
    }

    vector<vector<int>> graph = buildGraph(n, edges);
    int q = rnd.next(8, 28);

    println(n);
    for (auto [u, v] : edges) {
        println(u, v);
    }
    println(q);

    for (int qi = 0; qi < q; ++qi) {
        int i = rnd.next(1, n);
        int j = rnd.next(1, n);
        if (rnd.next(0, 5) == 0) {
            j = i;
        }

        vector<int> path = findPath(i, j, graph);
        if (rnd.next(0, 1) == 0) {
            int k = rnd.next(0, 2) == 0 ? rnd.any(path) : randomNodeOutsidePath(n, path);
            println(1, i, j, k);
        } else {
            pair<int, int> edge;
            if (path.size() >= 2 && rnd.next(0, 2) != 0) {
                int pos = rnd.next(0, int(path.size()) - 2);
                edge = {path[pos], path[pos + 1]};
            } else {
                edge = rnd.any(edges);
            }
            if (rnd.next(0, 1)) {
                swap(edge.first, edge.second);
            }
            println(2, i, j, edge.first, edge.second);
        }
    }

    return 0;
}
