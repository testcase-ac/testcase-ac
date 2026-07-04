#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i - 1, i});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.push_back({center, i});
        }
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(1, n);
    for (int i = 2; i <= handle; ++i) {
        edges.push_back({i - 1, i});
    }
    int hub = handle;
    for (int i = handle + 1; i <= n; ++i) {
        edges.push_back({hub, i});
    }
    return edges;
}

vector<pair<int, int>> makeBalanced(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

vector<pair<int, int>> makeRandomParentTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        int parent = rnd.next(1, i - 1);
        edges.push_back({parent, i});
    }
    return edges;
}

void relabelAndShuffle(vector<pair<int, int>>& edges, int n) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
}

vector<vector<int>> buildGraph(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    for (auto edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
    return graph;
}

vector<int> pathBetween(int start, int target, const vector<vector<int>>& graph) {
    vector<int> parent(graph.size(), 0);
    vector<int> stack = {start};
    parent[start] = -1;

    for (int i = 0; i < static_cast<int>(stack.size()); ++i) {
        int node = stack[i];
        if (node == target) {
            break;
        }
        for (int next : graph[node]) {
            if (parent[next] == 0) {
                parent[next] = node;
                stack.push_back(next);
            }
        }
    }

    vector<int> path;
    for (int node = target; node != -1; node = parent[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.wnext(14, -2) + 1;
    int q = rnd.next(1, 18);

    vector<pair<int, int>> edges;
    int mode = rnd.next(5);
    if (mode == 0) {
        edges = makePath(n);
    } else if (mode == 1) {
        edges = makeStar(n);
    } else if (mode == 2) {
        edges = makeBroom(n);
    } else if (mode == 3) {
        edges = makeBalanced(n);
    } else {
        edges = makeRandomParentTree(n);
    }

    relabelAndShuffle(edges, n);
    vector<vector<int>> graph = buildGraph(n, edges);

    println(n, q);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(6);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        int c = rnd.next(1, n);

        if (queryMode == 0) {
            b = a;
            c = a;
        } else if (queryMode == 1) {
            b = a;
        } else if (queryMode == 2) {
            c = b;
        } else if (queryMode == 3 && n > 1) {
            vector<int> path = pathBetween(a, b, graph);
            b = rnd.any(path);
            c = rnd.any(path);
        } else if (queryMode == 4 && n > 2) {
            vector<int> path = pathBetween(a, c, graph);
            b = path[path.size() / 2];
        }

        println(a, b, c);
    }

    return 0;
}
