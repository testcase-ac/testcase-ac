#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: weighted between small and moderate sizes [2,15]
    int tN = rnd.any(vector<int>{-1, 0, 1});
    int N = rnd.wnext(14, tN) + 2;  // rnd.wnext(14) → [0,13], +2 → [2,15]

    // Choose graph type for dependency diversity
    int gtype = rnd.next(0, 4);
    vector<pair<int,int>> edges;

    if (gtype == 1) {
        // Simple chain: 1->2->...->N
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i + 1);
    } else if (gtype == 2) {
        // Reversed chain: N->N-1->...->1
        for (int i = 1; i < N; i++)
            edges.emplace_back(i + 1, i);
    } else if (gtype == 3) {
        // Cycle: 1->2->...->N->1
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i + 1);
        edges.emplace_back(N, 1);
    } else if (gtype == 4) {
        // Star centered at a random center c
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == c) continue;
            if (rnd.next() < 0.5) edges.emplace_back(c, i);
            else edges.emplace_back(i, c);
        }
    } else {
        // Fully random directed edges, no self-loops
        int maxE = N * (N - 1);
        int maxM = min(maxE, 400);
        // Hyper-parameter for M: weighted selection in [1, maxM]
        int tM = rnd.any(vector<int>{-1, 0, 1});
        int M = rnd.wnext(maxM, tM) + 1; // → [1, maxM]
        vector<pair<int,int>> all;
        all.reserve(maxE);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (i != j)
                    all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        edges.insert(edges.end(), all.begin(), all.begin() + M);
    }

    // Ensure at least one dependency if none was added (fallback)
    if (edges.empty()) {
        // Add single random dependency
        int u = rnd.next(1, N), v = rnd.next(1, N);
        while (v == u) v = rnd.next(1, N);
        edges.emplace_back(u, v);
    }

    int M = (int)edges.size();
    // Generate mood changes
    vector<int> t(N);
    for (int i = 0; i < N; i++) {
        t[i] = rnd.next(-100000, 100000);
    }

    // Output
    println(N, M);
    for (int x : t) println(x);
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
