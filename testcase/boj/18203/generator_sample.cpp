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

int randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(0, 3);
    }
    if (mode == 1) {
        return rnd.next(0, 20);
    }
    return rnd.next(5000, 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? rnd.next(1, 3) : rnd.next(4, 14);
    int maxEdges = min(45, max(1, n * (n + 1) / 2));
    int m = rnd.next(max(1, n - 2), maxEdges);

    vector<Edge> edges;

    if (mode == 1 || mode == 2 || mode == 4) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n && (int)edges.size() < m; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            edges.push_back({parent, order[i], randomWeight(mode % 3)});
        }
    }

    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (mode != 3 && rnd.next(0, 4) != 0) {
            while (v == u && n > 1) {
                v = rnd.next(1, n);
            }
        }
        int w = randomWeight(mode % 3);
        if (mode == 2 && rnd.next(0, 2) == 0) {
            w = 0;
        }
        edges.push_back({u, v, w});

        if (mode == 3 && (int)edges.size() < m && rnd.next(0, 2) == 0) {
            edges.push_back({u, v, w});
        }
    }

    vector<int> balls;
    if (mode == 0) {
        balls.assign(7, rnd.next(1, n));
    } else {
        int favored = rnd.next(1, n);
        for (int i = 0; i < 7; ++i) {
            if (rnd.next(0, 3) == 0) {
                balls.push_back(favored);
            } else if (mode == 5 && i > 2) {
                balls.push_back(rnd.next(max(1, n / 2), n));
            } else {
                balls.push_back(rnd.next(1, n));
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, m);
    for (int i = 0; i < m; ++i) {
        println(edges[i].u, edges[i].v, edges[i].w);
    }
    println(balls);

    return 0;
}
