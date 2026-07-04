#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long c;
};

long long pickWeight(int profile) {
    if (profile == 0) {
        return rnd.next(1, 12);
    }
    if (profile == 1) {
        return rnd.next(1, 3) == 1 ? rnd.next(1, 5) : rnd.next(50, 120);
    }
    if (profile == 2) {
        return rnd.next(1, 4) == 1 ? 1000000000LL : rnd.next(999999900, 1000000000);
    }
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 14);
    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = 2;
    } else if (kMode == 2) {
        k = 1000000000LL;
    } else {
        k = rnd.next(1, 20);
    }

    vector<Edge> edges;
    int weightProfile = rnd.next(0, 3);

    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i, pickWeight(weightProfile)});
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({1, i, pickWeight(weightProfile)});
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            edges.push_back({i - 1, i, pickWeight(weightProfile)});
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i, pickWeight(weightProfile)});
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i, pickWeight(weightProfile)});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i, pickWeight(weightProfile)});
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (Edge& edge : edges) {
        edge.u = label[edge.u];
        edge.v = label[edge.v];
        if (rnd.next(0, 1) == 1) {
            swap(edge.u, edge.v);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, k);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.c);
    }

    return 0;
}
