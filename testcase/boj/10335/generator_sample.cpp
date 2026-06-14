#include "testlib.h"
#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, w});
    }
}

int chooseWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{1, 2, 3, 5, 8, 13, 10000});
    }
    if (mode == 2) {
        return rnd.next(9990, 10000);
    }
    return rnd.next(1, 10000);
}

void addRandomTree(vector<Edge>& edges, set<pair<int, int>>& used, int n, int weightMode) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(0, i - 1)];
        addEdge(edges, used, order[i], parent, chooseWeight(weightMode));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, mode == 4 ? 18 : 12);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        addRandomTree(edges, used, n, rnd.next(0, 3));
    } else if (mode == 1) {
        int cycleSize = rnd.next(3, min(n, 8));
        int tieWeight = rnd.next(1, 20);
        for (int i = 1; i <= cycleSize; ++i) {
            int j = i == cycleSize ? 1 : i + 1;
            addEdge(edges, used, i, j, tieWeight);
        }
        for (int v = cycleSize + 1; v <= n; ++v) {
            addEdge(edges, used, rnd.next(1, v - 1), v, chooseWeight(rnd.next(0, 3)));
        }
    } else if (mode == 2) {
        addRandomTree(edges, used, n, 0);
        int bridgeWeight = rnd.next(1, 5);
        for (int v = 2; v <= n; ++v) {
            if (rnd.next(0, 1)) {
                addEdge(edges, used, 1, v, bridgeWeight);
            }
        }
    } else if (mode == 3) {
        addRandomTree(edges, used, n, 3);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.35) {
                    addEdge(edges, used, i, j, chooseWeight(rnd.next(0, 3)));
                }
            }
        }
    } else {
        addRandomTree(edges, used, n, rnd.next(0, 3));
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (!used.count({i, j})) {
                    candidates.push_back({i, j});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = rnd.next(0, min<int>(candidates.size(), n + rnd.next(0, n)));
        for (int i = 0; i < extra; ++i) {
            addEdge(edges, used, candidates[i].first, candidates[i].second,
                    chooseWeight(rnd.next(0, 3)));
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
}
