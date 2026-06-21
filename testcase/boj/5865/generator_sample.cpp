#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int latency;
    int capacity;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int x = rnd.next(1, 2000);
    vector<Edge> edges;

    auto addEdge = [&](int u, int v, int latency, int capacity) {
        edges.push_back({u, v, latency, capacity});
    };

    if (mode == 0) {
        n = 2;
        int parallelCount = rnd.next(2, 8);
        x = rnd.next(1, 1000);
        for (int i = 0; i < parallelCount; ++i) {
            addEdge(1, 2, rnd.next(1, 80), rnd.next(1, 100));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        x = rnd.next(50, 2000);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 30), rnd.next(20, 200));
        }
        addEdge(1, n, rnd.next(1, 40), rnd.next(1, 15));
        int extras = rnd.next(0, n);
        for (int i = 0; i < extras; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            while (v == u) v = rnd.next(1, n);
            addEdge(u, v, rnd.next(1, 70), rnd.next(1, 200));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        x = rnd.next(1, 1000000);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin() + 1, order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(parent, order[i], rnd.next(1, 100), rnd.next(1, 1000));
        }
        int extras = rnd.next(n, 2 * n);
        for (int i = 0; i < extras; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            while (v == u) v = rnd.next(1, n);
            addEdge(u, v, rnd.next(1, 1000), rnd.next(1, 1000));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 8);
        x = rnd.next(100, 10000);
        int midA = 2;
        int midB = 3;
        addEdge(1, midA, rnd.next(1, 8), rnd.next(1, 8));
        addEdge(midA, n, rnd.next(1, 8), rnd.next(1, 8));
        addEdge(1, midB, rnd.next(20, 80), rnd.next(80, 500));
        addEdge(midB, n, rnd.next(20, 80), rnd.next(80, 500));
        for (int node = 4; node < n; ++node) {
            addEdge(rnd.next(1, node - 1), node, rnd.next(1, 60), rnd.next(1, 300));
            addEdge(node, rnd.next(node + 1, n), rnd.next(1, 60), rnd.next(1, 300));
        }
        addEdge(1, n, rnd.next(1, 120), rnd.next(1, 500));
    } else {
        n = rnd.next(2, 12);
        x = rnd.next(1, 5000);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 100), rnd.next(1, 100));
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 25) {
                    int copies = rnd.next(1, 3);
                    for (int copy = 0; copy < copies; ++copy) {
                        addEdge(i, j, rnd.next(1, 300), rnd.next(1, 300));
                    }
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), x);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.latency, edge.capacity);
    }

    return 0;
}
