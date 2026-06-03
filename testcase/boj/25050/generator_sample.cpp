#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
             long long w) {
    if (u == v || used.count({u, v})) {
        return;
    }
    used.insert({u, v});
    edges.push_back({u, v, w});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0 || mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            int u = label[i], v = label[i + 1];
            if (mode == 1) {
                swap(u, v);
            }
            addEdge(edges, used, u, v, rnd.next(1, 30));
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            int parent = rnd.next(0, i - 1);
            addEdge(edges, used, label[parent], label[i], rnd.next(1, 30));
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            int parent = rnd.next(0, i - 1);
            addEdge(edges, used, label[i], label[parent], rnd.next(1, 30));
        }
    } else if (mode == 4) {
        long long total = 0;
        for (int i = 0; i + 1 < n; ++i) {
            long long forward = rnd.next(1, 20);
            long long backward = rnd.next(1, 20);
            total += max(forward, backward);
            addEdge(edges, used, label[i], label[i + 1], forward);
            addEdge(edges, used, label[i + 1], label[i], backward);
        }

        int extra = rnd.next(0, min(8, n));
        for (int tries = 0; tries < 80 && extra > 0; ++tries) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            int diff = a > b ? a - b : b - a;
            if (diff <= 1) {
                continue;
            }
            long long w = total + 1000 + rnd.next(1, 1000);
            size_t before = edges.size();
            addEdge(edges, used, label[a], label[b], w);
            if (edges.size() != before) {
                --extra;
            }
        }
    } else {
        long long total = 0;
        for (int i = 0; i < n; ++i) {
            long long w = rnd.next(1, 20);
            total += w;
            addEdge(edges, used, label[i], label[(i + 1) % n], w);
        }

        int extra = rnd.next(0, min(8, n));
        for (int tries = 0; tries < 80 && extra > 0; ++tries) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            if (a == b || (a + 1) % n == b) {
                continue;
            }
            long long w = total + 1000 + rnd.next(1, 1000);
            size_t before = edges.size();
            addEdge(edges, used, label[a], label[b], w);
            if (edges.size() != before) {
                --extra;
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
