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

Edge makeEdge(int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    return {u, v, w};
}

int randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 15);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{1, 2, 4999, 5000});
    }
    return rnd.next(1, 5000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 4 ? 8 : 12);
    int s = rnd.next(1, n);

    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            edges.push_back(makeEdge(i, i + 1, randomWeight(mode)));
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.push_back(makeEdge(center, v, randomWeight(mode)));
            }
        }
    } else {
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(i)];
            edges.push_back(makeEdge(parent, vertices[i], randomWeight(mode)));
        }
    }

    set<pair<int, int>> simplePairs;
    for (const Edge& edge : edges) {
        simplePairs.insert({edge.u, edge.v});
    }

    if (mode == 2 || mode == 4) {
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int target = rnd.next(n - 1, min<int>(candidates.size(), n * (n - 1) / 2));
        for (auto [u, v] : candidates) {
            if ((int)edges.size() >= target) {
                break;
            }
            if (simplePairs.insert({u, v}).second) {
                edges.push_back({u, v, randomWeight(mode)});
            }
        }
    }

    if (mode == 3 || mode == 4) {
        int extra = rnd.next(1, min(12, 5000 - (int)edges.size()));
        for (int i = 0; i < extra; ++i) {
            const Edge& base = edges[rnd.next((int)edges.size())];
            edges.push_back({base.u, base.v, randomWeight(1)});
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    if (mode == 0) {
        if (rnd.next(2)) {
            reverse(order.begin(), order.end());
        }
    } else {
        shuffle(order.begin(), order.end());
    }

    if (rnd.next(3) == 0) {
        s = order[rnd.next(n)];
    }

    println(n, (int)edges.size(), s);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
    println(order);

    return 0;
}
