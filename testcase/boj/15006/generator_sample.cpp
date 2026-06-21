#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
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

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 12 : 15);

    vector<long long> dist(n, -1);
    vector<Edge> edges;
    set<pair<int, int>> used;
    dist[1] = 0;

    vector<int> order;
    for (int v = 0; v < n; ++v) {
        if (v != 1) {
            order.push_back(v);
        }
    }
    shuffle(order.begin(), order.end());

    vector<int> zeroGroup;
    if (mode == 4 && n >= 5) {
        int groupSize = rnd.next(2, min(4, n - 2));
        for (int i = 0; i < groupSize; ++i) {
            zeroGroup.push_back(order.back());
            order.pop_back();
        }
    }

    vector<int> built = {1};
    if (mode == 1 && n > 2) {
        int pos0 = int(find(order.begin(), order.end(), 0) - order.begin());
        if (pos0 < int(order.size())) {
            swap(order[0], order[pos0]);
        }
    }

    for (int v : order) {
        int parent;
        if (mode == 0 || (mode == 2 && rnd.next(0, 2) == 0)) {
            parent = 1;
        } else {
            parent = rnd.any(built);
        }
        int step = (mode == 3) ? rnd.next(1, 500) : rnd.next(1, 60);
        dist[v] = dist[parent] + step;
        addEdge(edges, used, v, parent, step);
        built.push_back(v);
    }

    if (!zeroGroup.empty()) {
        int parent = rnd.any(built);
        long long baseDist = dist[parent] + rnd.next(1, 60);
        int terminal = rnd.any(zeroGroup);
        for (int v : zeroGroup) {
            dist[v] = baseDist;
        }
        addEdge(edges, used, terminal, parent, int(baseDist - dist[parent]));
        for (int i = 1; i < int(zeroGroup.size()); ++i) {
            int parentInGroup = zeroGroup[rnd.next(0, i - 1)];
            addEdge(edges, used, zeroGroup[i], parentInGroup, 0);
        }
    }

    int maxExtra = min(n * (n - 1) / 2 - int(edges.size()), rnd.next(0, n + 6));
    vector<pair<int, int>> candidates;
    for (int a = 0; a < n; ++a) {
        for (int b = a + 1; b < n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto [a, b] : candidates) {
        if (maxExtra == 0) {
            break;
        }
        long long minNonShortest = abs(dist[a] - dist[b]) + 1;
        int extra = rnd.next(0, mode == 3 ? 1000 : 80);
        long long weight = minNonShortest + extra;
        if (weight > 500000) {
            continue;
        }
        addEdge(edges, used, a, b, int(weight));
        --maxExtra;
    }

    shuffle(edges.begin(), edges.end());
    println(n, int(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.w);
    }
    return 0;
}
