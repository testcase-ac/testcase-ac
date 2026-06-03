#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int from, int to, int weight) {
    if (from == to || used.count({from, to})) {
        return;
    }
    used.insert({from, to});
    edges.push_back({from, to, weight});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(3, mode == 3 ? 14 : 10);
    int hub = rnd.next(1, n);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            int from = order[i];
            int to = order[(i + 1) % n];
            addEdge(edges, used, from, to, rnd.next(1, 30));
        }
        if (rnd.next(0, 1)) {
            for (int i = 0; i < n; ++i) {
                int from = order[(i + 1) % n];
                int to = order[i];
                addEdge(edges, used, from, to, rnd.next(1, 30));
            }
        }
    } else {
        for (int city = 1; city <= n; ++city) {
            if (city == hub) {
                continue;
            }
            int outWeight = mode == 1 ? rnd.next(1, 8) : rnd.next(1, 1000);
            int backWeight = mode == 1 ? rnd.next(1, 8) : rnd.next(1, 1000);
            addEdge(edges, used, hub, city, outWeight);
            addEdge(edges, used, city, hub, backWeight);
        }
    }

    double extraProbability = mode == 0 ? rnd.next(0.05, 0.30) : rnd.next(0.10, 0.55);
    for (int from = 1; from <= n; ++from) {
        for (int to = 1; to <= n; ++to) {
            if (from != to && !used.count({from, to}) && rnd.next() < extraProbability) {
                int weight = mode == 2 ? rnd.next(600, 1000) : rnd.next(1, 80);
                addEdge(edges, used, from, to, weight);
            }
        }
    }

    vector<int> cities(n);
    for (int i = 0; i < n; ++i) {
        cities[i] = i + 1;
    }
    shuffle(cities.begin(), cities.end());
    int k = rnd.next(2, min(n, mode == 3 ? 8 : 5));
    vector<int> residents(cities.begin(), cities.begin() + k);
    if (mode == 1 && find(residents.begin(), residents.end(), hub) == residents.end() && rnd.next(0, 1)) {
        residents[rnd.next(0, k - 1)] = hub;
    }
    shuffle(edges.begin(), edges.end());
    shuffle(residents.begin(), residents.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.from, edge.to, edge.weight);
    }
    println(k);
    println(residents);

    return 0;
}
