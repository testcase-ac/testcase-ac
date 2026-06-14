#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int d;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    auto addEdge = [&](int a, int b, int d) {
        edges.push_back({a, b, d});
    };

    if (mode == 0) {
        n = rnd.next(2, 5);
        int w = rnd.next(1, 20);
        addEdge(1, n, w);
        addEdge(1, n, w + rnd.next(1, 20));
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        int direct = rnd.next(2, 30);
        addEdge(1, n, direct);
        int split = rnd.next(1, direct - 1);
        addEdge(1, 2, split);
        addEdge(2, n, direct - split + rnd.next(1, 15));
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 15));
        }
        int shortcutEnd = rnd.next(3, n);
        addEdge(1, shortcutEnd, rnd.next(1, 8));
        if (shortcutEnd != n) {
            addEdge(shortcutEnd, n, rnd.next(1, 8));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(2, 18));
        }
        int hub = rnd.next(2, n - 1);
        addEdge(1, hub, rnd.next(1, 10));
        addEdge(hub, n, rnd.next(1, 10));
        addEdge(hub, hub, rnd.next(1, 12));
    } else {
        n = rnd.next(5, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 25));
        }
        for (int i = 2; i + 1 <= n; ++i) {
            if (rnd.next(0, 1)) {
                addEdge(1, i, rnd.next(1, 30));
            }
            if (rnd.next(0, 1)) {
                addEdge(i, n, rnd.next(1, 30));
            }
        }
    }

    int extra = rnd.next(0, min(12, n + 4));
    for (int i = 0; i < extra; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (rnd.next(0, 3) != 0 && a == b) {
            b = rnd.next(1, n);
        }
        addEdge(a, b, rnd.next(1, 50));
    }

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    vector<int> middle;
    for (int i = 2; i < n; ++i) {
        middle.push_back(i);
    }
    shuffle(middle.begin(), middle.end());
    for (int i = 2; i < n; ++i) {
        perm[i] = middle[i - 2];
    }
    perm[1] = 1;
    perm[n] = n;

    for (Edge& edge : edges) {
        edge.a = perm[edge.a];
        edge.b = perm[edge.b];
        if (rnd.next(0, 1)) {
            swap(edge.a, edge.b);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.d);
    }

    return 0;
}
