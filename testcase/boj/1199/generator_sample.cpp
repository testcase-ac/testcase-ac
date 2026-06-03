#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

void addEdge(vector<vector<int>>& graph, int u, int v, int count = 1) {
    graph[u][v] += count;
    graph[v][u] += count;
}

void addRandomSpanningTree(vector<vector<int>>& graph, const vector<int>& order) {
    for (int i = 1; i < int(order.size()); ++i) {
        int parent = order[rnd.next(i)];
        addEdge(graph, order[i], parent);
    }
}

void addRandomExtraEdges(vector<vector<int>>& graph, int attempts, int maxAdd) {
    int n = int(graph.size());
    for (int it = 0; it < attempts; ++it) {
        int u = rnd.next(n);
        int v = rnd.next(n - 1);
        if (v >= u) {
            ++v;
        }

        int room = 10 - graph[u][v];
        if (room <= 0) {
            continue;
        }
        addEdge(graph, u, v, rnd.next(1, min(room, maxAdd)));
    }
}

void addRandomCycle(vector<vector<int>>& graph, vector<int> vertices, int count) {
    shuffle(vertices.begin(), vertices.end());
    for (int i = 0; i < int(vertices.size()); ++i) {
        addEdge(graph, vertices[i], vertices[(i + 1) % vertices.size()], count);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 4) {
        n = rnd.next(3, 10);
    } else if (mode == 5) {
        n = rnd.next(10, 18);
    } else {
        n = rnd.next(2, 10);
    }

    vector<vector<int>> graph(n, vector<int>(n));
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    if (n > 1) {
        if (mode == 1) {
            for (int i = 1; i < n; ++i) {
                addEdge(graph, i - 1, i);
            }
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                addEdge(graph, i, (i + 1) % n);
            }
            addRandomExtraEdges(graph, rnd.next(0, n), 2);
        } else if (mode == 3) {
            for (int i = 1; i < n; ++i) {
                addEdge(graph, 0, i, rnd.next(1, 5));
            }
        } else if (mode == 4) {
            addRandomSpanningTree(graph, order);
            for (int i = 0; i < rnd.next(1, 4); ++i) {
                vector<int> cycle = order;
                cycle.resize(rnd.next(3, n));
                addRandomCycle(graph, cycle, 2);
            }
        } else {
            addRandomSpanningTree(graph, order);
            addRandomExtraEdges(graph, rnd.next(n, 3 * n), 4);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(graph[i]);
    }

    return 0;
}
