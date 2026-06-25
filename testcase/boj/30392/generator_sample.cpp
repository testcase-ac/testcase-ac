#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

long long multipleUpTo(long long unit, long long limit) {
    long long maxMul = limit / unit;
    return unit * rnd.next(0LL, maxMul);
}

void addEdge(vector<Edge>& edges, int u, int v, long long w) {
    edges.push_back({u, v, w});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_W = 1000000000LL;
    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 10);
    long long k = rnd.next(1, 30);
    vector<Edge> edges;

    if (mode == 0) {
        k = rnd.next(1, 30);
    } else if (mode == 1) {
        if (k % 2 == 0) ++k;
        int m = rnd.next(1, 12);
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            long long w = multipleUpTo(k, MAX_W);
            if (i == 0 && rnd.next(0, 1) == 1) w += rnd.next(1LL, min(k - 1, 9LL));
            addEdge(edges, u, v, w);
        }
    } else if (mode == 2) {
        if (k % 2 == 1) ++k;
        long long half = k / 2;
        int leftSize = rnd.next(1, max(1, n - 1));
        vector<int> color(n + 1);
        for (int i = 1; i <= n; ++i) color[i] = (i <= leftSize ? 0 : 1);

        int m = rnd.next(1, 12);
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            bool crosses = color[u] != color[v];
            long long base = crosses ? half : k;
            addEdge(edges, u, v, multipleUpTo(base, MAX_W));
        }
    } else if (mode == 3) {
        if (k % 2 == 1) ++k;
        long long half = k / 2;
        n = max(n, 3);
        addEdge(edges, 1, 2, half);
        addEdge(edges, 2, 3, half);
        addEdge(edges, 3, 1, half);
        int extra = rnd.next(0, 6);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            addEdge(edges, u, v, multipleUpTo(half, MAX_W));
        }
    } else if (mode == 4) {
        k = rnd.next(1, 30);
        int u = rnd.next(1, n);
        addEdge(edges, u, u, rnd.next(0LL, min(MAX_W, 60LL)));
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            int v = rnd.next(1, n);
            addEdge(edges, u, v, rnd.next(0LL, min(MAX_W, 60LL)));
        }
    } else {
        k = rnd.next(1, 30);
        n = max(n, 2);
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        addEdge(edges, u, v, rnd.next(0LL, min(MAX_W, 60LL)));
        addEdge(edges, u, v, rnd.next(0LL, min(MAX_W, 60LL)));
        addEdge(edges, v, u, rnd.next(0LL, min(MAX_W, 60LL)));
        int extra = rnd.next(0, 6);
        for (int i = 0; i < extra; ++i) {
            addEdge(edges, rnd.next(1, n), rnd.next(1, n), rnd.next(0LL, min(MAX_W, 60LL)));
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()), k);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
