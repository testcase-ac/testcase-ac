#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct GraphBuilder {
    int n;
    set<pair<int, int>> seen;
    vector<pair<int, int>> edges;

    explicit GraphBuilder(int n_) : n(n_) {}

    void addEdge(int u, int v) {
        if (u == v) {
            return;
        }
        if (u > v) {
            swap(u, v);
        }
        if (seen.insert({u, v}).second) {
            edges.push_back({u, v});
        }
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(4);

    vector<int> label(n);
    for (int i = 0; i < n; ++i) {
        label[i] = i + 1;
    }
    shuffle(label.begin(), label.end());

    int coreSize = rnd.next(2, n);
    int s = label[0];
    int t = label[coreSize - 1];
    GraphBuilder graph(n);

    if (mode == 0) {
        for (int i = 0; i + 1 < coreSize; ++i) {
            graph.addEdge(label[i], label[i + 1]);
        }
        for (int i = 0; i < coreSize; ++i) {
            for (int j = i + 2; j < coreSize; ++j) {
                if (rnd.next(100) < 25) {
                    graph.addEdge(label[i], label[j]);
                }
            }
        }
    } else if (mode == 1) {
        int layers = rnd.next(2, min(5, coreSize));
        vector<vector<int>> byLayer(layers);
        byLayer[0].push_back(label[0]);
        byLayer[layers - 1].push_back(label[coreSize - 1]);
        int nextVertex = 1;
        for (int i = 1; i + 1 < layers; ++i) {
            byLayer[i].push_back(label[nextVertex++]);
        }
        while (nextVertex + 1 < coreSize) {
            byLayer[rnd.next(1, layers - 1)].push_back(label[nextVertex++]);
        }
        for (int i = 0; i + 1 < layers; ++i) {
            for (int u : byLayer[i]) {
                int v = rnd.any(byLayer[i + 1]);
                graph.addEdge(u, v);
            }
            for (int v : byLayer[i + 1]) {
                int u = rnd.any(byLayer[i]);
                graph.addEdge(u, v);
            }
        }
        for (int i = 0; i + 1 < layers; ++i) {
            for (int u : byLayer[i]) {
                for (int v : byLayer[i + 1]) {
                    if (rnd.next(100) < 45) {
                        graph.addEdge(u, v);
                    }
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i < coreSize; ++i) {
            graph.addEdge(label[i], label[rnd.next(i)]);
        }
        int density = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(100) < density) {
                    graph.addEdge(label[i], label[j]);
                }
            }
        }
    } else {
        for (int i = 0; i + 1 < coreSize; ++i) {
            graph.addEdge(label[i], label[i + 1]);
        }
        for (int i = coreSize; i < n; ++i) {
            graph.addEdge(label[i], label[rnd.next(coreSize)]);
        }
        for (int i = 1; coreSize < n && i + 1 < coreSize; ++i) {
            if (rnd.next(100) < 35) {
                graph.addEdge(label[i], label[coreSize + rnd.next(n - coreSize)]);
            }
        }
    }

    if (coreSize < n && mode != 3) {
        for (int i = coreSize; i < n; ++i) {
            if (rnd.next(100) < 55) {
                graph.addEdge(label[i], label[rnd.next(i)]);
            }
        }
    }

    shuffle(graph.edges.begin(), graph.edges.end());
    for (auto& edge : graph.edges) {
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }

    println(n, static_cast<int>(graph.edges.size()), s, t);
    for (const auto& edge : graph.edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
