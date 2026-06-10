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

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int c) {
    if (u == v || used.count({u, v})) {
        return;
    }
    used.insert({u, v});
    edges.push_back({u, v, c});
}

int randomCost() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.next(1, 2000);
    }
    if (mode == 2) {
        return rnd.next(4999990, 5000000);
    }
    return rnd.next(1, 5000000);
}

vector<int> randomPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 9);
    int mode = rnd.next(0, 5);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int wanted = rnd.next(0, min(n - 1, n * (n - 1)));
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < wanted && i < int(candidates.size()); ++i) {
            addEdge(edges, used, candidates[i].first, candidates[i].second, randomCost());
        }
    } else if (mode == 1) {
        vector<int> p = randomPermutation(n);
        int cycleCost = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            addEdge(edges, used, p[i], p[(i + 1) % n], cycleCost + rnd.next(0, 5));
        }

        int extra = rnd.next(0, n * (n - 1) - n);
        for (int tries = 0; tries < n * n * 3 && extra > 0; ++tries) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u != v && !used.count({u, v})) {
                int c = rnd.next(1, 100) <= 70 ? rnd.next(cycleCost + 20, 500) : randomCost();
                addEdge(edges, used, u, v, c);
                --extra;
            }
        }
    } else if (mode == 2) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v) {
                    addEdge(edges, used, u, v, randomCost());
                }
            }
        }
    } else if (mode == 3) {
        vector<int> p = randomPermutation(n);
        int low = rnd.next(1, 100);
        int high = rnd.next(low + 1, 5000000);
        for (int i = 0; i + 1 < n; ++i) {
            addEdge(edges, used, p[i], p[i + 1], low);
        }
        addEdge(edges, used, p[n - 1], p[0], high);

        for (int i = 0; i < n; ++i) {
            int j = rnd.next(0, n - 1);
            if (i != j) {
                addEdge(edges, used, p[i], p[j], rnd.next(low, high));
            }
        }
    } else if (mode == 4) {
        double density = rnd.next(0.15, 0.65);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next() < density) {
                    addEdge(edges, used, u, v, randomCost());
                }
            }
        }
    } else {
        vector<int> p = randomPermutation(n);
        int missing = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != missing) {
                addEdge(edges, used, p[i], p[(i + 1) % n], randomCost());
            }
        }
        for (int i = 0; i < n; ++i) {
            int v = p[rnd.next(0, n - 1)];
            addEdge(edges, used, p[i], v, randomCost());
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.c);
    }

    return 0;
}
