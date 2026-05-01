#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for manual verification
    int N = rnd.next(2, 12);
    vector<pair<int,int>> edges;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    auto addEdge = [&](int u, int v) {
        if (u > v) swap(u, v);
        if (!used[u][v]) {
            used[u][v] = true;
            edges.emplace_back(u, v);
        }
    };

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Simple path 1-2-...-N
        for (int u = 1; u < N; ++u)
            addEdge(u, u+1);
    } else if (mode == 1) {
        // Random tree
        for (int u = 2; u <= N; ++u)
            addEdge(u, rnd.next(1, u-1));
    } else if (mode == 2) {
        // Star graph centered at random c
        int c = rnd.next(1, N);
        for (int u = 1; u <= N; ++u)
            if (u != c) addEdge(c, u);
    } else if (mode == 3) {
        // Random tree + some extra edges
        for (int u = 2; u <= N; ++u)
            addEdge(u, rnd.next(1, u-1));
        int extra = rnd.wnext(N, 1);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, N), v = rnd.next(1, N);
            if (u != v) addEdge(u, v);
        }
    } else {
        // Complete graph for very small N, else random graph
        if (N <= 8) {
            for (int u = 1; u <= N; ++u)
                for (int v = u+1; v <= N; ++v)
                    addEdge(u, v);
        } else {
            // Ensure connectivity via tree
            for (int u = 2; u <= N; ++u)
                addEdge(u, rnd.next(1, u-1));
            // Add some random extras
            int extra = rnd.next(0, N/2);
            for (int i = 0; i < extra; ++i) {
                int u = rnd.next(1, N), v = rnd.next(1, N);
                if (u != v) addEdge(u, v);
            }
        }
    }

    // Randomize edge order
    shuffle(edges.begin(), edges.end());
    // Output
    println(N, (int)edges.size());
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
