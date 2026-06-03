#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int w) {
    if (a > b) {
        swap(a, b);
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, w});
    }
}

static void addRandomExtras(vector<Edge>& edges, set<pair<int, int>>& used, int n, int targetM, int lo, int hi) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= targetM) {
            break;
        }
        addEdge(edges, used, a, b, rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(2, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 20));
        }
        addRandomExtras(edges, used, n, rnd.next(n - 1, min(n * (n - 1) / 2, n + 8)), 5, 60);
    } else if (mode == 1) {
        n = rnd.next(4, 14);
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 8));
        }
        for (int i = split; i < n; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 8));
        }
        addEdge(edges, used, 1, split, rnd.next(2, 15));
        addEdge(edges, used, split - 1, n, rnd.next(2, 15));
        addRandomExtras(edges, used, n, rnd.next((int)edges.size(), min(n * (n - 1) / 2, n + 10)), 10, 80);
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        int hub = rnd.next(2, n - 1);
        addEdge(edges, used, 1, hub, rnd.next(1, 12));
        addEdge(edges, used, hub, n, rnd.next(1, 12));
        for (int v = 2; v < n; ++v) {
            if (v != hub) {
                addEdge(edges, used, hub, v, rnd.next(2, 30));
            }
        }
        addRandomExtras(edges, used, n, rnd.next(n - 1, min(n * (n - 1) / 2, 2 * n)), 1, 100);
    } else if (mode == 3) {
        n = rnd.next(5, 18);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin() + 1, order.end() - 1);
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(i)];
            addEdge(edges, used, parent, order[i], rnd.next(1, 50));
        }
        addRandomExtras(edges, used, n, rnd.next(n - 1, min(n * (n - 1) / 2, 3 * n)), 1, 1000);
    } else {
        n = rnd.next(6, 15);
        int maxM = n * (n - 1) / 2;
        int targetM = rnd.next(max(n - 1, maxM / 2), maxM);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 25));
        }
        addRandomExtras(edges, used, n, targetM, 1, 1000000);
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.w);
    }

    return 0;
}
