#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int weightForMode(int mode, bool initialTreeEdge) {
    if (mode == 0) {
        return initialTreeEdge ? rnd.next(20, 100) : rnd.next(1, 30);
    }
    if (mode == 1) {
        return initialTreeEdge ? rnd.next(1, 40) : rnd.next(35, 80);
    }
    if (mode == 2) {
        return rnd.next(1, 12);
    }
    if (rnd.next(4) == 0) {
        return rnd.next(1, 3);
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int treeMode = rnd.next(4);
    int weightMode = rnd.next(4);

    vector<Edge> edges;
    edges.reserve(40);

    if (treeMode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v, weightForMode(weightMode, true)});
        }
    } else if (treeMode == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v, weightForMode(weightMode, true)});
        }
    } else if (treeMode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({rnd.next(1, v - 1), v, weightForMode(weightMode, true)});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent = max(1, v - rnd.next(1, min(3, v - 1)));
            edges.push_back({parent, v, weightForMode(weightMode, true)});
        }
    }

    int extraLimit = min(26, max(1, n * (n - 1) / 2));
    int extraEdges = rnd.next(0, extraLimit);
    for (int i = 0; i < extraEdges; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) {
            ++v;
        }

        if (rnd.next(5) == 0) {
            const Edge& treeEdge = rnd.any(edges);
            u = treeEdge.u;
            v = treeEdge.v;
        }

        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        edges.push_back({u, v, weightForMode(weightMode, false)});
    }

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
