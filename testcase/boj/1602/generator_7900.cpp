#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 12);
    // Decide number of components for variability (to allow unreachable)
    int C = rnd.next(1, min(N, 4));
    // Assign each node to a component
    vector<int> comp_ids(N);
    for (int i = 0; i < N; i++) comp_ids[i] = i % C;
    shuffle(comp_ids.begin(), comp_ids.end());
    vector<vector<int>> compNodes(C);
    for (int i = 0; i < N; i++) {
        compNodes[comp_ids[i]].push_back(i);
    }
    // Build edges: first a spanning forest
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    for (int ci = 0; ci < C; ci++) {
        auto &nodes = compNodes[ci];
        int sz = nodes.size();
        for (int j = 1; j < sz; j++) {
            int u = nodes[j];
            int v = nodes[rnd.next(0, j-1)];
            int a = u+1, b = v+1;
            if (a > b) swap(a, b);
            used.insert({a,b});
            edges.emplace_back(a, b);
        }
    }
    // Candidate extra edges within same component
    vector<pair<int,int>> cand;
    for (int ci = 0; ci < C; ci++) {
        auto &nodes = compNodes[ci];
        int sz = nodes.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i+1; j < sz; j++) {
                int a = nodes[i]+1, b = nodes[j]+1;
                if (a > b) swap(a, b);
                if (!used.count({a,b})) {
                    cand.emplace_back(a, b);
                }
            }
        }
    }
    // Add random extra edges
    shuffle(cand.begin(), cand.end());
    int extra = cand.empty() ? 0 : rnd.next(0, (int)cand.size());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }
    int M = edges.size();
    // Generate node harassment times
    vector<int> h(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        if (p < 0.6) h[i] = rnd.next(1, 50);
        else if (p < 0.95) h[i] = rnd.next(51, 500);
        else h[i] = rnd.next(501, 10000);
    }
    // Generate edge weights
    vector<int> w(M);
    for (int i = 0; i < M; i++) {
        if (rnd.next() < 0.7) w[i] = rnd.next(1, 20);
        else w[i] = rnd.next(21, 100);
    }
    // Number of queries
    int Qmax = min(20, N * 3);
    int Q = rnd.next(1, Qmax);
    vector<pair<int,int>> queries;
    for (int i = 0; i < Q; i++) {
        if (rnd.next() < 0.2) {
            // trivial query S = T
            int x = rnd.next(1, N);
            queries.emplace_back(x, x);
        } else if (C > 1 && rnd.next() < 0.3) {
            // unreachable query across components
            int c1 = rnd.next(0, C-1), c2 = rnd.next(0, C-1);
            while (c2 == c1) c2 = rnd.next(0, C-1);
            int u = rnd.any(compNodes[c1]) + 1;
            int v = rnd.any(compNodes[c2]) + 1;
            queries.emplace_back(u, v);
        } else {
            // general S != T
            int u = rnd.next(1, N), v = rnd.next(1, N);
            while (v == u) v = rnd.next(1, N);
            queries.emplace_back(u, v);
        }
    }

    // Output
    println(N, M, Q);
    println(h);
    for (int i = 0; i < M; i++) {
        println(edges[i].first, edges[i].second, w[i]);
    }
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}
