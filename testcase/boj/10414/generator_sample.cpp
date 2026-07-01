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

int nextCost(int mode) {
    if (mode == 0) {
        return rnd.next(1, 12);
    }
    if (mode == 1) {
        return rnd.next(9900, 10000);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{1, 2, 3, 9999, 10000});
    }
    return rnd.next(1, 10000);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, w});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int p = 0;
    if (mode == 2) {
        p = n;
    } else if (mode == 3) {
        p = 1;
    } else {
        p = rnd.next(1, min(n - 1, 5));
    }

    vector<int> vertices;
    for (int i = 1; i <= n; ++i) {
        vertices.push_back(i);
    }
    shuffle(vertices.begin(), vertices.end());

    vector<int> insecure(vertices.begin(), vertices.begin() + p);
    sort(insecure.begin(), insecure.end());

    vector<bool> isInsecure(n + 1, false);
    for (int v : insecure) {
        isInsecure[v] = true;
    }

    vector<int> secure;
    for (int v = 1; v <= n; ++v) {
        if (!isInsecure[v]) {
            secure.push_back(v);
        }
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    int costMode = rnd.next(0, 3);

    if (mode == 2) {
        double density = rnd.next(0.15, 0.55);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) {
                    addEdge(edges, used, i, j, nextCost(costMode));
                }
            }
        }
    } else {
        if (mode != 1 && secure.size() >= 2) {
            vector<int> order = secure;
            shuffle(order.begin(), order.end());
            for (int i = 1; i < (int)order.size(); ++i) {
                int parent = order[rnd.next(0, i - 1)];
                addEdge(edges, used, order[i], parent, nextCost(costMode));
            }
        }

        for (int v : insecure) {
            if (!secure.empty() && (mode != 4 || rnd.next(0, 2) > 0)) {
                int links = rnd.next(1, min<int>(3, secure.size()));
                vector<int> endpoints = secure;
                shuffle(endpoints.begin(), endpoints.end());
                for (int i = 0; i < links; ++i) {
                    addEdge(edges, used, v, endpoints[i], nextCost(costMode));
                }
            } else if (n >= 2 && rnd.next(0, 1)) {
                int other = rnd.any(vertices);
                while (other == v) {
                    other = rnd.any(vertices);
                }
                addEdge(edges, used, v, other, nextCost(costMode));
            }
        }

        double secureDensity = mode == 3 ? rnd.next(0.0, 0.2) : rnd.next(0.15, 0.55);
        for (int i = 0; i < (int)secure.size(); ++i) {
            for (int j = i + 1; j < (int)secure.size(); ++j) {
                if (rnd.next() < secureDensity) {
                    addEdge(edges, used, secure[i], secure[j], nextCost(costMode));
                }
            }
        }

        if (mode == 5) {
            double mixedDensity = rnd.next(0.05, 0.25);
            for (int u : insecure) {
                for (int v = 1; v <= n; ++v) {
                    if (u != v && rnd.next() < mixedDensity) {
                        addEdge(edges, used, u, v, nextCost(costMode));
                    }
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), p);
    if (insecure.empty()) {
        println("");
    } else {
        println(insecure);
    }
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
