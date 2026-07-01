#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, set<Edge>& seen, int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    if (seen.insert({u, v}).second) {
        edges.push_back({u, v});
    }
}

vector<Edge> pathGraph(int n) {
    vector<Edge> edges;
    set<Edge> seen;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, seen, i, i + 1);
    }
    return edges;
}

vector<Edge> starGraph(int n) {
    vector<Edge> edges;
    set<Edge> seen;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            addEdge(edges, seen, center, v);
        }
    }
    return edges;
}

vector<Edge> cycleGraph(int n) {
    vector<Edge> edges = pathGraph(n);
    set<Edge> seen(edges.begin(), edges.end());
    addEdge(edges, seen, 1, n);
    return edges;
}

vector<Edge> cliqueGraph(int n) {
    vector<Edge> edges;
    set<Edge> seen;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            addEdge(edges, seen, u, v);
        }
    }
    return edges;
}

vector<Edge> randomConnectedGraph(int n) {
    vector<Edge> edges;
    set<Edge> seen;
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(0, i - 1)];
        addEdge(edges, seen, parent, order[i]);
    }

    double density = rnd.next(0.0, 0.65);
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!seen.count({u, v}) && rnd.next() < density) {
                addEdge(edges, seen, u, v);
            }
        }
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    if (mode == 0) {
        n = rnd.next(2, 5);
        edges = pathGraph(n);
    } else if (mode == 1) {
        edges = starGraph(n);
    } else if (mode == 2) {
        edges = cycleGraph(n);
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        edges = cliqueGraph(n);
    } else {
        edges = randomConnectedGraph(n);
    }

    shuffle(edges.begin(), edges.end());
    for (auto& [u, v] : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(u, v);
        }
    }

    println(n, static_cast<int>(edges.size()));
    for (const auto& [u, v] : edges) {
        println(u, v);
    }
    return 0;
}
