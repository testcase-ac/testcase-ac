#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

static void addEdge(vector<Edge>& edges, int u, int v, int w) {
    edges.emplace_back(u, v, w);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1, rnd.next(-9, 12));
    }

    if (mode == 0) {
        int shortcuts = rnd.next(1, n);
        for (int i = 0; i < shortcuts; ++i) {
            int u = rnd.next(1, n - 1);
            int v = rnd.next(u + 1, n);
            addEdge(edges, u, v, rnd.next(-20, 25));
        }
    } else if (mode == 1 && n >= 3) {
        int a = rnd.next(1, n - 2);
        addEdge(edges, a, a + 1, rnd.next(1, 20));
        addEdge(edges, a + 1, a, rnd.next(0, 20));
        addEdge(edges, a + 1, n, rnd.next(-5, 15));
    } else if (mode == 2 && n >= 4) {
        int a = rnd.next(2, n - 2);
        addEdge(edges, a, a + 1, rnd.next(1, 15));
        addEdge(edges, a + 1, a, rnd.next(1, 15));
        addEdge(edges, 1, n, rnd.next(-10, 10));
    } else if (mode == 3) {
        int tries = rnd.next(n, n * 3);
        for (int i = 0; i < tries; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            addEdge(edges, u, v, rnd.next(-30, 30));
        }
    } else {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next() < 0.28) {
                    addEdge(edges, u, v, rnd.next(-12, 18));
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }

    return 0;
}
