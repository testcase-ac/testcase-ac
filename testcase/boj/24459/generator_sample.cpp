#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int chooseWeight(int pattern, int index) {
    if (pattern == 0) {
        return rnd.next(1, 12);
    }
    if (pattern == 1) {
        return rnd.next(9990, 10000);
    }
    if (pattern == 2) {
        return (index % 2 == 0) ? rnd.next(1, 3) : rnd.next(9000, 10000);
    }
    return rnd.any(vector<int>{1, 2, 7, 37, 9999, 10000});
}

void addEdge(vector<Edge>& edges, int u, int v, int weightPattern) {
    edges.push_back({u, v, chooseWeight(weightPattern, static_cast<int>(edges.size()))});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int weightPattern = rnd.next(0, 3);

    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i - 1, i, weightPattern);
        }
    } else if (mode == 1) {
        int center = rnd.next(0, n - 1);
        for (int v = 0; v < n; ++v) {
            if (v != center) {
                addEdge(edges, center, v, weightPattern);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i - 1, i, weightPattern);
        }
        for (int v = spine; v < n; ++v) {
            addEdge(edges, rnd.next(0, spine - 1), v, weightPattern);
        }
    } else if (mode == 3) {
        for (int v = 1; v < n; ++v) {
            addEdge(edges, (v - 1) / 2, v, weightPattern);
        }
    } else {
        for (int v = 1; v < n; ++v) {
            addEdge(edges, rnd.next(0, v - 1), v, weightPattern);
        }
    }

    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto edge : edges) {
        int u = label[edge.u];
        int v = label[edge.v];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v, edge.w);
    }

    return 0;
}
