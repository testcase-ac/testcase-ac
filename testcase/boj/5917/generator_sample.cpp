#include "testlib.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

void addEdge(map<pair<int, int>, int>& edges, int a, int b, int w) {
    if (a > b) {
        swap(a, b);
    }
    edges[{a, b}] = w;
}

void addRandomExtraEdges(map<pair<int, int>, int>& edges, int n, int targetM,
                         int minW, int maxW) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!edges.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= targetM) {
            break;
        }
        addEdge(edges, a, b, rnd.next(minW, maxW));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    map<pair<int, int>, int> edges;

    if (mode == 0) {
        n = rnd.next(2, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 30));
        }
        addRandomExtraEdges(edges, n, rnd.next(n - 1, min(n * (n - 1) / 2, n + 8)), 1, 80);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        int split = rnd.next(2, n - 2);
        for (int i = 1; i < split; ++i) {
            addEdge(edges, i, i + 1, rnd.next(2, 20));
        }
        for (int i = split; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(2, 20));
        }
        addEdge(edges, 1, split, rnd.next(3, 35));
        addEdge(edges, split, n, rnd.next(3, 35));
        addEdge(edges, 1, n, rnd.next(30, 90));
        addRandomExtraEdges(edges, n, rnd.next((int)edges.size(), min(n * (n - 1) / 2, n + 10)), 1, 90);
    } else if (mode == 2) {
        n = rnd.next(6, 14);
        int chainW = rnd.next(1, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, chainW + rnd.next(0, 3));
        }
        for (int i = 1; i + 2 <= n; ++i) {
            if (rnd.next(0, 1)) {
                addEdge(edges, i, i + 2, 2 * chainW + rnd.next(-1, 8));
            }
        }
        addRandomExtraEdges(edges, n, rnd.next(n - 1, min(n * (n - 1) / 2, 2 * n)), 1, 60);
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, 1, v, rnd.next(1, 50));
        }
        for (int v = 2; v < n; ++v) {
            addEdge(edges, v, n, rnd.next(1, 50));
        }
        addRandomExtraEdges(edges, n, rnd.next((int)edges.size(), min(n * (n - 1) / 2, 2 * n + 4)), 1, 100);
    } else if (mode == 4) {
        n = rnd.next(8, 16);
        vector<vector<int>> layer(4);
        layer[0].push_back(1);
        layer[3].push_back(n);
        for (int v = 2; v < n; ++v) {
            layer[rnd.next(1, 2)].push_back(v);
        }
        if (layer[1].empty()) {
            layer[1].push_back(layer[2].back());
            layer[2].pop_back();
        }
        if (layer[2].empty()) {
            layer[2].push_back(layer[1].back());
            layer[1].pop_back();
        }
        for (int i = 0; i < 3; ++i) {
            for (int a : layer[i]) {
                int b = rnd.any(layer[i + 1]);
                addEdge(edges, a, b, rnd.next(1, 40));
            }
            for (int b : layer[i + 1]) {
                int a = rnd.any(layer[i]);
                addEdge(edges, a, b, rnd.next(1, 40));
            }
        }
        addRandomExtraEdges(edges, n, rnd.next((int)edges.size(), min(n * (n - 1) / 2, 3 * n)), 1, 80);
    } else {
        n = rnd.next(5, 13);
        int targetM = rnd.next(n - 1, min(n * (n - 1) / 2, 35));
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 1000000));
        }
        addRandomExtraEdges(edges, n, targetM, 1, 1000000);
    }

    vector<Edge> out;
    for (auto [endpoints, w] : edges) {
        out.push_back({endpoints.first, endpoints.second, w});
    }
    shuffle(out.begin(), out.end());

    println(n, (int)out.size());
    for (const Edge& e : out) {
        println(e.a, e.b, e.w);
    }

    return 0;
}
