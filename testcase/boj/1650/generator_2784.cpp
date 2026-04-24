#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of farms
    int N = rnd.next(3, 10);

    // Create a shuffled list of intermediate nodes (2..N-1)
    vector<int> pool;
    for (int i = 2; i < N; i++) pool.push_back(i);
    shuffle(pool.begin(), pool.end());

    // Hyper-parameters: how many intermediates on each of the two edge‐disjoint paths
    int max_mid = (int)pool.size();
    int t1 = rnd.next(0, max_mid);
    int t2 = rnd.next(0, max_mid - t1);

    vector<int> mid1(pool.begin(), pool.begin() + t1);
    vector<int> mid2(pool.begin() + t1, pool.begin() + t1 + t2);

    // Build the two guaranteed edge-disjoint paths from 1 to N
    vector<pair<int,int>> edges;
    auto addE = [&](int u, int v) {
        int a = min(u,v), b = max(u,v);
        edges.emplace_back(a, b);
    };
    int prev = 1;
    for (int x : mid1) { addE(prev, x); prev = x; }
    addE(prev, N);

    prev = 1;
    for (int x : mid2) { addE(prev, x); prev = x; }
    addE(prev, N);

    // Collect all possible remaining edges
    set<pair<int,int>> used(edges.begin(), edges.end());
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            pair<int,int> e = {i, j};
            if (!used.count(e)) cand.push_back(e);
        }
    }
    shuffle(cand.begin(), cand.end());

    // Hyper-parameter: how many extra edges to add
    int extra = rnd.next(0, (int)cand.size());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }

    // Shuffle final edge list
    shuffle(edges.begin(), edges.end());

    // Hyper-parameters for weights
    int wmin = rnd.next(1, 10);
    int wmax = rnd.next(wmin, 50);

    // Output
    int M = (int)edges.size();
    println(N, M);
    for (auto &e : edges) {
        int w = rnd.next(wmin, wmax);
        println(e.first, e.second, w);
    }

    return 0;
}
