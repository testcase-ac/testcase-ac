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

static void addEdge(vector<Edge>& edges, int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    edges.push_back({u, v, w});
}

static void addRandomEdge(vector<Edge>& edges, int n, int minW, int maxW) {
    int u = rnd.next(1, n);
    int v = rnd.next(1, n - 1);
    if (v >= u) {
        ++v;
    }
    addEdge(edges, u, v, rnd.next(minW, maxW));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(10, 15);
    int x = 1;
    int z = n;
    vector<int> ys;
    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 9));
        }
        addEdge(edges, x, z, rnd.next(40, 90));
        addEdge(edges, 2, n - 2, rnd.next(1, 6));
        addEdge(edges, 3, n - 1, rnd.next(10, 30));
        ys = {rnd.next(2, n - 1), rnd.next(2, n - 1)};
    } else if (mode == 1) {
        for (int i = 1; i <= n / 2 - 1; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 20));
        }
        for (int i = n / 2 + 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 20));
        }
        ys = {rnd.next(2, n / 2), rnd.next(n / 2 + 1, n - 1)};
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(5, 25));
        }
        int a = rnd.next(2, n - 2);
        addEdge(edges, a, a + 1, rnd.next(1, 4));
        addEdge(edges, a, a + 1, rnd.next(60, 120));
        addEdge(edges, x, a, rnd.next(1, 5));
        addEdge(edges, a + 1, z, rnd.next(1, 5));
        ys = {a, a + 1};
    } else if (mode == 3) {
        int hub = rnd.next(2, n - 1);
        for (int i = 1; i <= n; ++i) {
            if (i != hub) {
                addEdge(edges, hub, i, rnd.next(1, 30));
            }
        }
        addEdge(edges, x, z, rnd.next(80, 150));
        addEdge(edges, x, hub, rnd.next(1, 5));
        ys = {hub, rnd.next(2, n - 1)};
    } else {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 40));
        }
        int extra = rnd.next(6, 18);
        for (int i = 0; i < extra; ++i) {
            addRandomEdge(edges, n, 1, 100);
        }
        ys = {rnd.next(2, n - 1), rnd.next(2, n - 1), rnd.next(2, n - 1)};
    }

    while ((int)edges.size() < 10) {
        addRandomEdge(edges, n, 1, 100);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    auto relabel = [&](int v) {
        return order[v - 1];
    };

    vector<int> intermediates;
    vector<int> used(n + 1);
    for (int y : ys) {
        int ry = relabel(y);
        if (ry != relabel(x) && ry != relabel(z) && !used[ry]) {
            used[ry] = 1;
            intermediates.push_back(ry);
        }
    }
    int targetP = rnd.next(max(1, (int)intermediates.size()), n - 3);
    for (int v = 1; (int)intermediates.size() < targetP; ++v) {
        int rv = relabel(v);
        if (rv != relabel(x) && rv != relabel(z) && !used[rv]) {
            used[rv] = 1;
            intermediates.push_back(rv);
        }
    }
    shuffle(intermediates.begin(), intermediates.end());

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& e : edges) {
        println(relabel(e.u), relabel(e.v), e.w);
    }
    println(relabel(x), relabel(z));
    println((int)intermediates.size());
    println(intermediates);

    return 0;
}
