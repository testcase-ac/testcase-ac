#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int style = rnd.next(0, 5);
    int N;
    vector<pair<int,int>> edges;

    if (style == 0) {
        // Path (tree) with possible extra edges / duplicates
        N = rnd.next(3, 12);
        for (int i = 1; i < N; ++i)
            edges.push_back({i, i + 1});

        // Sometimes add a duplicate of an existing edge
        if (rnd.next(0, 2) == 0) {
            pair<int,int> e = edges[rnd.next(0, (int)edges.size() - 1)];
            edges.push_back(e);
        }
        // Sometimes add 1-2 chords (non-adjacent if possible)
        if (rnd.next(0, 1) == 0) {
            int cnt = rnd.next(1, 2);
            for (int t = 0; t < cnt; ++t) {
                int u, v;
                int attempts = 0;
                do {
                    u = rnd.next(1, N);
                    v = rnd.next(1, N);
                    attempts++;
                } while ((u == v || abs(u - v) <= 1) && attempts < 10);
                if (u == v) v = (u % N) + 1;
                edges.push_back({u, v});
            }
        }
    } else if (style == 1) {
        // Single cycle with a few extra edges (possibly parallel)
        N = rnd.next(3, 12);
        for (int i = 1; i < N; ++i)
            edges.push_back({i, i + 1});
        edges.push_back({N, 1});

        int K = rnd.next(0, 3);
        for (int t = 0; t < K; ++t) {
            if (rnd.next(0, 1) == 0) {
                // duplicate an existing cycle edge
                pair<int,int> e = edges[rnd.next(0, (int)edges.size() - 1)];
                edges.push_back(e);
            } else {
                // random extra edge
                int u = rnd.next(1, N);
                int v = rnd.next(1, N);
                while (u == v) v = rnd.next(1, N);
                edges.push_back({u, v});
            }
        }
    } else if (style == 2) {
        // Two cycles connected by (at least) one bridge, plus some extras
        N = rnd.next(6, 12);
        int n1 = rnd.next(3, N - 3);
        int n2 = N - n1; // >= 3

        // left cycle: 1..n1
        for (int i = 1; i < n1; ++i)
            edges.push_back({i, i + 1});
        edges.push_back({n1, 1});

        // right cycle: n1+1..N
        for (int i = n1 + 1; i < N; ++i)
            edges.push_back({i, i + 1});
        edges.push_back({N, n1 + 1});

        // bridge between the two cycles
        int u = rnd.next(1, n1);
        int v = rnd.next(n1 + 1, N);
        edges.push_back({u, v});

        // extras within each cycle
        for (int side = 0; side < 2; ++side) {
            int K = rnd.next(0, 2);
            for (int t = 0; t < K; ++t) {
                if (rnd.next(0, 1) == 0) {
                    // duplicate an existing edge on that side
                    // (pick from all edges but biased: just pick any existing)
                    pair<int,int> e = edges[rnd.next(0, (int)edges.size() - 1)];
                    edges.push_back(e);
                } else {
                    int a, b;
                    if (side == 0) {
                        a = rnd.next(1, n1);
                        b = rnd.next(1, n1);
                        while (a == b) b = rnd.next(1, n1);
                    } else {
                        a = rnd.next(n1 + 1, N);
                        b = rnd.next(n1 + 1, N);
                        while (a == b) b = rnd.next(n1 + 1, N);
                    }
                    edges.push_back({a, b});
                }
            }
        }

        // sometimes add extra cross edges, potentially killing the bridge
        if (rnd.next(0, 1) == 0) {
            int extraCross = rnd.next(0, 2);
            for (int t = 0; t < extraCross; ++t) {
                int a = rnd.next(1, n1);
                int b = rnd.next(n1 + 1, N);
                edges.push_back({a, b});
            }
        }
    } else if (style == 3) {
        // Star centered at 1, with some leaves interconnected / parallel edges
        N = rnd.next(4, 12);
        for (int i = 2; i <= N; ++i)
            edges.push_back({1, i});

        int K = rnd.next(0, min(3, N - 1));
        for (int t = 0; t < K; ++t) {
            if (rnd.next(0, 1) == 0) {
                // duplicate center-leaf edge
                int leaf = rnd.next(2, N);
                edges.push_back({1, leaf});
            } else {
                // connect two leaves
                int u = rnd.next(2, N);
                int v = rnd.next(2, N);
                while (u == v) v = rnd.next(2, N);
                edges.push_back({u, v});
            }
        }
    } else if (style == 4) {
        // Path with many parallel edges and possibly a long back edge
        N = rnd.next(3, 10);
        for (int i = 1; i < N; ++i)
            edges.push_back({i, i + 1});

        for (int i = 1; i < N; ++i) {
            if (rnd.next(0, 1) == 0)
                edges.push_back({i, i + 1});
            if (rnd.next(0, 3) == 0)
                edges.push_back({i, i + 1});
        }

        if (N >= 4 && rnd.next(0, 1) == 0) {
            int u = rnd.next(1, N - 2);
            int v = rnd.next(u + 2, N);
            edges.push_back({u, v});
        }
    } else if (style == 5) {
        // Random connected graph: random tree + extra edges / duplicates
        N = rnd.next(3, 10);
        for (int v = 2; v <= N; ++v) {
            int p = rnd.next(1, v - 1);
            edges.push_back({p, v});
        }
        int extraEdges = rnd.next(0, N + 3);
        for (int t = 0; t < extraEdges; ++t) {
            if (rnd.next(0, 1) == 0 && !edges.empty()) {
                // duplicate existing edge
                pair<int,int> e = edges[rnd.next(0, (int)edges.size() - 1)];
                edges.push_back(e);
            } else {
                int u = rnd.next(1, N);
                int v = rnd.next(1, N);
                while (u == v) v = rnd.next(1, N);
                edges.push_back({u, v});
            }
        }
    }

    // Optionally permute vertex labels for diversity
    if (rnd.next(0, 1) == 0) {
        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        for (auto &e : edges) {
            e.first = perm[e.first];
            e.second = perm[e.second];
        }
    }

    int M = (int)edges.size();
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
