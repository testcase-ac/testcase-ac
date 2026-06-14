#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int c;
};

int randomCost(bool largeCosts) {
    if (largeCosts && rnd.next(3) == 0) {
        return rnd.next(50000000, 100000000);
    }
    return rnd.next(1, largeCosts ? 1000000 : 30);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
             bool largeCosts) {
    if (u == v) {
        return;
    }
    auto key = minmax(u, v);
    if (!used.insert(key).second) {
        return;
    }
    edges.push_back({u, v, randomCost(largeCosts)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    bool largeCosts = (mode == 4);
    int k = largeCosts ? rnd.next(100000, 200000) : rnd.next(2, 20);

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        // Sparse connected floor graph.
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, largeCosts);
        }
        int extra = rnd.next(0, min(4, n * (n - 1) / 2 - (n - 1)));
        for (int it = 0; it < 50 && extra > 0; ++it) {
            int before = edges.size();
            addEdge(edges, used, rnd.next(1, n), rnd.next(1, n), largeCosts);
            if ((int)edges.size() > before) {
                --extra;
            }
        }
    } else if (mode == 1) {
        // Room N may be separated on every floor unless an elevator helps.
        for (int i = 1; i + 1 < n; ++i) {
            if (rnd.next(2) == 0) {
                addEdge(edges, used, i, i + 1, largeCosts);
            }
        }
        if (edges.empty()) {
            addEdge(edges, used, 1, n == 2 ? 2 : 2, largeCosts);
        }
    } else if (mode == 2) {
        // Dense small graph with shuffled corridor directions.
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(100) < 65) {
                    addEdge(edges, used, i, j, largeCosts);
                }
            }
        }
        if (edges.empty()) {
            addEdge(edges, used, 1, n, largeCosts);
        }
    } else if (mode == 3) {
        // Star or hub-like layout where one elevator can dominate.
        int hub = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != hub && rnd.next(100) < 80) {
                addEdge(edges, used, hub, i, largeCosts);
            }
        }
        if (edges.empty()) {
            addEdge(edges, used, 1, n, largeCosts);
        }
    } else {
        // Compact case with large weights and floor count.
        n = rnd.next(2, 8);
        k = rnd.next(100000, 200000);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, largeCosts);
        }
        if (n > 3) {
            addEdge(edges, used, 1, n, largeCosts);
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(2) == 0) {
            swap(edge.u, edge.v);
        }
    }

    vector<int> elevators(n, -1);
    int elevatorMode = rnd.next(4);
    for (int i = 0; i < n; ++i) {
        bool hasElevator = false;
        if (elevatorMode == 0) {
            hasElevator = false;
        } else if (elevatorMode == 1) {
            hasElevator = true;
        } else {
            hasElevator = rnd.next(100) < (elevatorMode == 2 ? 35 : 70);
        }

        if (hasElevator) {
            elevators[i] = largeCosts ? randomCost(true) : rnd.next(1, 15);
        }
    }
    if (rnd.next(3) == 0) {
        elevators[rnd.next(n)] = largeCosts ? rnd.next(50000000, 100000000)
                                            : rnd.next(1, 15);
    }

    println(n, (int)edges.size(), k);
    for (const auto& edge : edges) {
        println(edge.u, edge.v, edge.c);
    }
    println(elevators);

    return 0;
}
