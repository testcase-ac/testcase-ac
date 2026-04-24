#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small graph size
    int N = rnd.next(2, 10);
    int maxEdges = N * (N - 1) / 2;

    // Choose sparsity strategy
    int strat = rnd.next(0, 2);
    int M;
    if (strat == 0) {
        // Very sparse: 1 to N-1 edges
        M = rnd.next(1, min(N - 1, maxEdges));
    } else if (strat == 1) {
        // Moderate: between N and maxEdges if possible, else 1..maxEdges
        if (maxEdges >= N)
            M = rnd.next(N, maxEdges);
        else
            M = rnd.next(1, maxEdges);
    } else {
        // Dense: close to full
        int L = max(1, maxEdges - (N - 1));
        M = rnd.next(L, maxEdges);
    }

    // Possibly enforce connectivity
    bool enforceConn = (rnd.next() < 0.5) && (M >= N - 1);
    vector<pair<int,int>> edges;
    if (enforceConn) {
        // Build a random spanning tree
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        set<pair<int,int>> inTree;
        for (int i = 1; i < N; i++) {
            int u = perm[i];
            int v = perm[rnd.next(0, i - 1)];
            if (u > v) swap(u, v);
            edges.emplace_back(u, v);
            inTree.insert({u, v});
        }
        // Remaining edges
        vector<pair<int,int>> cand;
        for (int u = 1; u <= N; u++) {
            for (int v = u + 1; v <= N; v++) {
                if (!inTree.count({u, v}))
                    cand.emplace_back(u, v);
            }
        }
        shuffle(cand.begin(), cand.end());
        int need = M - (N - 1);
        for (int i = 0; i < need; i++)
            edges.push_back(cand[i]);
    } else {
        // Just pick M random edges
        vector<pair<int,int>> all;
        for (int u = 1; u <= N; u++)
            for (int v = u + 1; v <= N; v++)
                all.emplace_back(u, v);
        shuffle(all.begin(), all.end());
        edges.assign(all.begin(), all.begin() + M);
    }
    // Shuffle final edge order
    shuffle(edges.begin(), edges.end());

    // Choose weight strategy
    int wstrat = rnd.next(0, 1);
    int weightMax;
    if (wstrat == 0) {
        weightMax = rnd.next(M, M * 5);
    } else {
        weightMax = rnd.next(max(M, 100), 1000000);
    }
    // Generate M distinct weights
    set<int> wset;
    while ((int)wset.size() < M) {
        wset.insert(rnd.next(1, weightMax));
    }
    vector<int> weights(wset.begin(), wset.end());
    shuffle(weights.begin(), weights.end());

    // Number of queries
    int maxPairs = N * (N - 1);
    int Q = rnd.next(1, min(maxPairs, 10));

    // Output
    println(N, M);
    for (int i = 0; i < M; i++) {
        println(edges[i].first, edges[i].second, weights[i]);
    }
    println(Q);
    for (int i = 0; i < Q; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        while (y == x) y = rnd.next(1, N);
        println(x, y);
    }

    return 0;
}
