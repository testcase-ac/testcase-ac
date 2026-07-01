#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    long long sum;
};

void addEdge(vector<Edge>& edges, const vector<long long>& value, int u, int v) {
    edges.push_back({u, v, value[u] + value[v]});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    vector<long long> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        value[i] = rnd.next(-20, 20);
    }

    vector<Edge> edges;

    if (mode == 0) {
        // A single self-loop fixes one value exactly.
        n = rnd.next(1, 8);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        addEdge(edges, value, 1, 1);
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, value, i - 1, i);
        }
    } else if (mode == 1) {
        // Odd cycle fixes the component.
        n = rnd.next(3, 10);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        addEdge(edges, value, 1, 2);
        addEdge(edges, value, 2, 3);
        addEdge(edges, value, 3, 1);
        for (int i = 4; i <= n; ++i) {
            addEdge(edges, value, rnd.next(1, i - 1), i);
        }
    } else if (mode == 2) {
        // Pure bipartite/tree-shaped information leaves multiple answers.
        n = rnd.next(2, 12);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, value, rnd.next(1, i - 1), i);
        }
        int extra = rnd.next(0, min(5, n));
        for (int e = 0; e < extra; ++e) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if ((u % 2) == (v % 2)) {
                v = (v % n) + 1;
            }
            addEdge(edges, value, u, v);
        }
    } else if (mode == 3) {
        // Two components: one fixed, one intentionally ambiguous.
        n = rnd.next(5, 12);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        addEdge(edges, value, 1, 2);
        addEdge(edges, value, 2, 3);
        addEdge(edges, value, 3, 1);
        for (int i = 5; i <= n; ++i) {
            addEdge(edges, value, rnd.next(4, i - 1), i);
        }
        addEdge(edges, value, 4, min(5, n));
    } else if (mode == 4) {
        // Unique solution with duplicate and reversed records.
        n = rnd.next(3, 9);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        addEdge(edges, value, 1, 2);
        addEdge(edges, value, 2, 3);
        addEdge(edges, value, 3, 1);
        for (int i = 4; i <= n; ++i) {
            addEdge(edges, value, i - 1, i);
        }
        int repeats = rnd.next(1, 4);
        for (int e = 0; e < repeats; ++e) {
            Edge base = rnd.any(edges);
            addEdge(edges, value, base.v, base.u);
        }
    } else {
        // Sparse valid input, including the N=1 ambiguous edge case.
        n = rnd.next(1, 8);
        value.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            value[i] = rnd.next(-20, 20);
        }
        int m = rnd.next(1, max(1, n + 2));
        for (int e = 0; e < m; ++e) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (n > 1 && rnd.next(0, 3) != 0 && u == v) {
                v = (v % n) + 1;
            }
            addEdge(edges, value, u, v);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.sum);
    }

    return 0;
}
