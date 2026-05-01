#include "testlib.h"
#include <vector>
using namespace std;

struct Edge {
    int a, b, c;
};

int genWeight(int u, int v, int wp) {
    if (wp == 0) {
        // Simple small random weights
        return rnd.next(1, 20);
    } else if (wp == 1) {
        // Structured but small weights depending on nodes
        return 1 + ((u * 3 + v * 7 + rnd.next(0, 3)) % 20);
    } else {
        // Mixed distribution: many small, some medium, few larger
        int coin = rnd.next(0, 99);
        if (coin < 60) return rnd.next(1, 5);       // very cheap
        if (coin < 85) return rnd.next(6, 15);      // medium
        return rnd.next(16, 100);                   // relatively expensive
    }
}

bool hasEdge(const vector<Edge> &edges, int u, int v) {
    for (const auto &e : edges) {
        if ((e.a == u && e.b == v) || (e.a == v && e.b == u))
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N, biased to have variety but always small
    int styleN = rnd.next(0, 2);
    int N;
    if (styleN == 0)      N = rnd.next(2, 4);
    else if (styleN == 1) N = rnd.next(5, 7);
    else                  N = rnd.next(8, 10);

    int t = rnd.next(1, 10);          // increment per conquest
    int wp = rnd.next(0, 2);          // weight pattern

    vector<Edge> edges;

    // Choose base tree shape to ensure connectivity
    int treeShape = rnd.next(0, 2);
    if (treeShape == 0) {
        // Path: 1-2-...-N
        for (int i = 1; i <= N - 1; ++i) {
            edges.push_back({i, i + 1, genWeight(i, i + 1, wp)});
        }
    } else if (treeShape == 1) {
        // Star centered at 1
        for (int v = 2; v <= N; ++v) {
            edges.push_back({1, v, genWeight(1, v, wp)});
        }
    } else {
        // Random tree
        for (int v = 2; v <= N; ++v) {
            int u = rnd.next(1, v - 1);
            edges.push_back({u, v, genWeight(u, v, wp)});
        }
    }

    // Add a few extra edges (cycles), keeping graph small and connected
    int maxPossible = N * (N - 1) / 2;
    int usedNow = (int)edges.size(); // N-1
    int maxExtraPossible = maxPossible - usedNow;
    int extraCap = min(maxExtraPossible, rnd.next(0, 5));  // up to 5 extras

    for (int k = 0; k < extraCap; ++k) {
        // Try a few times to find a new, non-duplicate edge
        bool added = false;
        for (int attempt = 0; attempt < 20 && !added; ++attempt) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) continue;
            if (hasEdge(edges, u, v)) continue;
            edges.push_back({u, v, genWeight(u, v, wp)});
            added = true;
        }
    }

    int M = (int)edges.size();
    println(N, M, t);
    for (const auto &e : edges) {
        println(e.a, e.b, e.c);
    }

    return 0;
}
