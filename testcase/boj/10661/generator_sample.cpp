#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int cost;
};

int randomCost(int mode, int index) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return 1000 - rnd.next(0, 20);
    if (mode == 2) return (index % 2 == 0) ? rnd.next(1, 30) : rnd.next(900, 1000);
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 4);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(0, 3);
        int n;
        if (mode == 0) {
            n = 2;
        } else if (mode == 1) {
            n = 2 * rnd.next(2, 5);
        } else {
            n = 2 * rnd.next(3, 8);
        }

        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        set<pair<int, int>> used;
        vector<Edge> edges;

        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int u = order[i];
            int v = order[rnd.next(0, i - 1)];
            auto key = minmax(u, v);
            used.insert(key);
            edges.push_back({u, v, randomCost(mode, i)});
        }

        int maxM = static_cast<int>(candidates.size());
        int m;
        if (mode == 0) {
            m = n - 1;
        } else if (mode == 1) {
            m = rnd.next(n - 1, min(maxM, n + 3));
        } else if (mode == 2) {
            m = rnd.next(n - 1, min(maxM, 2 * n));
        } else {
            m = rnd.next(max(n - 1, maxM - n), maxM);
        }

        for (auto [u, v] : candidates) {
            if (static_cast<int>(edges.size()) == m) break;
            auto key = minmax(u, v);
            if (used.count(key)) continue;
            used.insert(key);
            edges.push_back({u, v, randomCost(mode, static_cast<int>(edges.size()))});
        }

        shuffle(edges.begin(), edges.end());
        println(n, static_cast<int>(edges.size()));
        for (const Edge& edge : edges) {
            if (rnd.next(0, 1) == 0) {
                println(edge.u, edge.v, edge.cost);
            } else {
                println(edge.v, edge.u, edge.cost);
            }
        }
    }

    println(0, 0);
    return 0;
}
