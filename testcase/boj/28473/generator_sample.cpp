#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int digit;
    int cost;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int digit, int cost) {
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, digit, cost});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<Edge> edges;
    set<pair<int, int>> used;

    auto randomDigit = [&]() {
        if (rnd.next(0, 5) == 0) return rnd.any(vector<int>{1, 9});
        return rnd.next(1, 9);
    };
    auto randomCost = [&]() {
        int kind = rnd.next(0, 5);
        if (kind == 0) return 0;
        if (kind == 1) return rnd.next(0, 20);
        if (kind == 2) return rnd.next(999990, 1000000);
        return rnd.next(0, 1000000);
    };

    if (mode == 0) {
        n = rnd.next(3, 8);
        int left = rnd.next(2, n - 1);
        for (int i = 1; i < left; ++i) {
            addEdge(edges, used, i, i + 1, randomDigit(), randomCost());
        }
        for (int i = left + 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, randomDigit(), randomCost());
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());

        if (mode == 1) {
            for (int i = 1; i < n; ++i) {
                addEdge(edges, used, order[i - 1], order[i], randomDigit(), randomCost());
            }
        } else if (mode == 2) {
            int center = order[0];
            for (int i = 1; i < n; ++i) {
                addEdge(edges, used, center, order[i], rnd.next(1, 3), rnd.next(0, 50));
            }
        } else {
            for (int i = 1; i < n; ++i) {
                int parent = rnd.next(0, i - 1);
                addEdge(edges, used, order[parent], order[i], randomDigit(), randomCost());
            }
        }

        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!used.count({u, v})) candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int extraLimit = static_cast<int>(candidates.size());
        int extra = 0;
        if (mode == 3) {
            extra = rnd.next(0, min(extraLimit, n));
        } else if (mode == 4) {
            extra = rnd.next(min(extraLimit, n), extraLimit);
        } else if (mode == 5) {
            extra = rnd.next(0, min(extraLimit, 2 * n));
        }

        for (int i = 0; i < extra; ++i) {
            auto [u, v] = candidates[i];
            int digit = randomDigit();
            int cost = randomCost();
            if (mode == 5 && rnd.next(0, 2) == 0) {
                digit = rnd.next(1, 2);
                cost = rnd.next(500000, 1000000);
            }
            addEdge(edges, used, u, v, digit, cost);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.digit, edge.cost);
    }

    return 0;
}
