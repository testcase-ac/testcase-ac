#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small to medium graph
    int N = rnd.next(8, 12);
    // B such that 2*B <= N
    int B = rnd.next(1, N/2);
    // M between N-1 and min(2*N, N*(N-1)/2)
    int maxEdges = min(2*N, N*(N-1)/2);
    int M = rnd.next(N-1, maxEdges);

    // Generate a random spanning tree
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int,int>> treeEdges;
    set<pair<int,int>> used;
    vector<tuple<int,int,int>> edges;
    for (int i = 1; i < N; i++) {
        int u = nodes[i];
        int v = nodes[rnd.next(0, i-1)];
        if (u > v) swap(u, v);
        int w = rnd.next(1, 2000);
        treeEdges.emplace_back(u, v);
        used.insert({u, v});
        edges.emplace_back(u, v, w);
    }
    // Add extra edges (with some duplicates)
    int extra = M - (N - 1);
    double dupProb = rnd.next(); // probability to duplicate a tree edge
    while (extra > 0) {
        if (!treeEdges.empty() && rnd.next() < dupProb) {
            // parallel to a tree edge
            auto e = rnd.any(treeEdges);
            int w = rnd.next(1, 2000);
            edges.emplace_back(e.first, e.second, w);
        } else {
            int u = rnd.next(1, N), v = rnd.next(1, N);
            if (u == v) continue;
            int a = min(u, v), b = max(u, v);
            if (used.count({a, b})) continue;
            used.insert({a, b});
            int w = rnd.next(1, 2000);
            edges.emplace_back(a, b, w);
        }
        extra--;
    }
    shuffle(edges.begin(), edges.end());

    // Prepare queries
    vector<pair<int,int>> qs;
    for (int i = 0; i < B; i++) {
        int P, Q;
        if (i == 0) {
            P = 1;
            Q = rnd.next(1, N);
        } else if (i == 1) {
            P = rnd.next(2, N);
            Q = 1;
        } else if (i == 2) {
            P = rnd.next(1, N);
            Q = P;
        } else {
            P = rnd.next(1, N);
            Q = rnd.next(1, N);
        }
        qs.emplace_back(P, Q);
    }

    // Output
    println(N, M, B);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    for (auto &q : qs) {
        println(q.first, q.second);
    }
    return 0;
}
