#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 5);
    int N, M;
    int A, B;
    long long C;
    vector<Edge> edges;

    if (mode == 1) {
        // Mode 1: Based on Example 1 graph with varied C
        N = 5;
        A = 1; B = 3;
        vector<Edge> base = {
            {1, 2, 5},
            {2, 3, 5},
            {1, 4, 1},
            {4, 5, 6},
            {5, 3, 1}
        };
        vector<long long> Cs = {7, 8, 9, 10, 11};
        C = rnd.any(Cs);

        // Permute vertex labels
        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        A = perm[A];
        B = perm[B];

        for (auto e : base) {
            edges.push_back({perm[e.u], perm[e.v], e.w});
        }
    } else if (mode == 2) {
        // Mode 2: Based on Example 3 graph with varied C
        N = 5;
        A = 1; B = 3;
        vector<Edge> base = {
            {1, 2, 5},
            {2, 3, 5},
            {1, 4, 2},
            {4, 5, 6},
            {5, 3, 2}
        };
        vector<long long> Cs = {7, 9, 10, 11};
        C = rnd.any(Cs);

        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        A = perm[A];
        B = perm[B];

        for (auto e : base) {
            edges.push_back({perm[e.u], perm[e.v], e.w});
        }
    } else if (mode == 3) {
        // Mode 3: Based on Example 4 graph with varied C
        N = 3;
        A = 1; B = 3;
        vector<Edge> base = {
            {1, 2, 6},
            {2, 3, 6},
            {1, 3, 10}
        };
        vector<long long> Cs = {9, 10, 11, 12, 13};
        C = rnd.any(Cs);

        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        A = perm[A];
        B = perm[B];

        for (auto e : base) {
            edges.push_back({perm[e.u], perm[e.v], e.w});
        }
    } else if (mode == 4) {
        // Mode 4: Parallel paths with extra edges
        N = 4;
        A = 1; B = 4;
        vector<Edge> base = {
            {1, 2, 1},
            {2, 4, 9},
            {1, 3, 5},
            {3, 4, 5},
            {2, 3, 7},
            {1, 4, 11}
        };
        C = rnd.next(5, 15); // some budgets infeasible, some feasible

        vector<int> perm(N + 1);
        for (int i = 1; i <= N; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());
        A = perm[A];
        B = perm[B];

        for (auto e : base) {
            edges.push_back({perm[e.u], perm[e.v], e.w});
        }
    } else {
        // Mode 5: Chain with large weights + some extra edges (overflow / long long stress)
        N = rnd.next(5, 8);
        A = 1;
        B = N;
        long long chainSum = 0;
        // Build chain
        for (int i = 1; i < N; ++i) {
            long long w = 1000000000LL - rnd.next(0, 100000000); // [9e8, 1e9]
            edges.push_back({i, i + 1, w});
            chainSum += w;
        }
        // Add a few extra edges
        int maxExtra = N * (N - 1) / 2 - (N - 1);
        int K = 0;
        if (maxExtra > 0) {
            K = rnd.next(0, min(4, maxExtra));
        }

        vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
        for (auto &e : edges) {
            used[e.u][e.v] = used[e.v][e.u] = true;
        }

        int added = 0;
        while (added < K) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            if (u == v) continue;
            if (used[u][v]) continue;
            used[u][v] = used[v][u] = true;
            long long w;
            if (rnd.next(0, 1) == 0) {
                w = rnd.next(1, 1000); // some small edges
            } else {
                w = 1000000000LL - rnd.next(0, 100000000); // large edges again
            }
            edges.push_back({u, v, w});
            ++added;
        }

        // Choose diverse budgets around chainSum and very large
        vector<long long> Cs;
        long long sub = rnd.next(0LL, chainSum / 2 + 1);
        long long c1 = chainSum - sub;
        if (c1 < 1) c1 = 1;
        Cs.push_back(c1);
        Cs.push_back(chainSum);
        Cs.push_back(chainSum + rnd.next(1LL, 1000000000LL));
        Cs.push_back(100000000000000LL - rnd.next(0LL, 1000LL)); // up to 1e14

        C = rnd.any(Cs);
    }

    M = (int)edges.size();

    println(N, M, A, B, C);
    for (auto &e : edges) {
        println(e.u, e.v, e.w);
    }

    return 0;
}
