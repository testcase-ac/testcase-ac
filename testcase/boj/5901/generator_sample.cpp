#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.next(1, 1000);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{1, 2, 999, 1000});
    }
    return rnd.next(1, 50);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k = rnd.next(1, 5);
    int n = rnd.next(k + 1, 14);
    int weightMode = rnd.next(0, 3);

    vector<int> towns(n);
    iota(towns.begin(), towns.end(), 1);
    shuffle(towns.begin(), towns.end());

    vector<int> markets(towns.begin(), towns.begin() + k);
    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i, randomWeight(weightMode)});
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i, randomWeight(weightMode)});
        }
    } else if (mode == 2) {
        int hub = towns[0];
        for (int i = 1; i <= n; ++i) {
            if (i != hub) {
                edges.push_back({hub, i, randomWeight(weightMode)});
            }
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            int parent = max(1, i - rnd.next(1, min(i - 1, 3)));
            edges.push_back({parent, i, randomWeight(weightMode)});
        }
    }

    int extra = rnd.next(0, min(24, n * 2));
    for (int i = 0; i < extra; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (mode != 4 && u == v && rnd.next(0, 3) != 0) {
            v = u % n + 1;
        }
        edges.push_back({u, v, randomWeight(weightMode)});
    }

    if (rnd.next(0, 2) == 0 && !edges.empty()) {
        Edge base = rnd.any(edges);
        edges.push_back({base.u, base.v, randomWeight(weightMode)});
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), k);
    for (int market : markets) {
        println(market);
    }
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
