#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int time;
    int cost;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
                    int time, int cost) {
    if (u > v) swap(u, v);
    if (!used.insert({u, v}).second) return;
    edges.push_back({u, v, time, cost});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(0, 5);
    int maxRoads = n * (n - 1) / 2;
    int targetRoads = rnd.next(n - 1, min(maxRoads, n + rnd.next(0, 18)));

    vector<Edge> edges;
    set<pair<int, int>> used;

    vector<int> order;
    for (int i = 2; i < n; ++i) order.push_back(i);
    shuffle(order.begin(), order.end());

    int backboneLen = rnd.next(1, min(n - 1, 5));
    vector<int> path = {1};
    for (int i = 0; i + 1 < backboneLen; ++i) path.push_back(order[i]);
    path.push_back(n);

    int pathTime = 0;
    int pathCost = 0;
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        int time = rnd.next(1, mode == 1 ? 40 : 200);
        int cost = rnd.next(1, mode == 2 ? 700 : 2500);
        pathTime += time;
        pathCost += cost;
        addEdge(edges, used, path[i], path[i + 1], time, cost);
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto [u, v] : candidates) {
        if ((int)edges.size() >= targetRoads) break;

        int time;
        int cost;
        if (mode == 3 && (u == 1 || v == n)) {
            time = rnd.next(1, 35);
            cost = rnd.next(1500, 5000);
        } else if (mode == 4) {
            time = rnd.next(150, 1200);
            cost = rnd.next(1, 300);
        } else {
            time = rnd.next(1, 400);
            cost = rnd.next(1, 4000);
        }
        addEdge(edges, used, u, v, time, cost);
    }

    int t;
    int m;
    if (mode == 0) {
        t = rnd.next(max(1, pathTime), min(10000, pathTime + 500));
        m = rnd.next(min(10000, pathCost), 10000);
    } else if (mode == 1) {
        t = rnd.next(1, max(1, pathTime - 1));
        m = rnd.next(0, 10000);
    } else if (mode == 2) {
        t = rnd.next(max(1, pathTime), min(10000, pathTime + 700));
        m = rnd.next(0, max(0, min(10000, pathCost - 1)));
    } else if (mode == 3) {
        t = rnd.next(1, min(10000, max(1, pathTime + rnd.next(0, 120))));
        m = rnd.next(0, min(10000, max(0, pathCost + rnd.next(-1000, 1000))));
    } else {
        t = rnd.next(1, 10000);
        m = rnd.next(0, 10000);
    }

    shuffle(edges.begin(), edges.end());

    println(n);
    println(t, m);
    println((int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.time, edge.cost);
    }

    return 0;
}
