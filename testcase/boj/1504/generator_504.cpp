#include "testlib.h"
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(2, 10); // Number of vertices (small for easy verification)
    int maxE = N * (N - 1) / 2; // Maximum possible edges in an undirected graph
    int E = rnd.next(0, maxE); // Number of edges (can be zero)

    println(N, E);

    set<pair<int, int>> edges;

    // Generate E edges
    while ((int)edges.size() < E) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v) continue; // No self-loops
        if (u > v) swap(u, v);
        if (edges.count({u, v})) continue; // Avoid duplicate edges
        int c = rnd.next(1, 10); // Edge cost between 1 and 10
        edges.insert({u, v});
        println(u, v, c);
    }

    // Generate v1 and v2 satisfying the conditions
    int v1, v2;
    do {
        v1 = rnd.next(1, N);
    } while (v1 == N); // v1 ≠ N

    do {
        v2 = rnd.next(1, N);
    } while (v2 == 1 || v2 == v1); // v2 ≠ 1 and v2 ≠ v1

    println(v1, v2);

    return 0;
}
