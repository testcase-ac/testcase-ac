#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of cities
    int N = rnd.next(2, 15);

    // Weight scale hyper-parameter for diversity
    vector<int> wScales = {10, 100, 1000, 1000000};
    int wScale = rnd.any(wScales);

    // Build the tree with diverse shapes
    vector<tuple<int,int,int>> eds;
    int treeType = rnd.next(0, 3);
    if (treeType == 0) {
        // chain
        for (int i = 2; i <= N; i++)
            eds.emplace_back(i-1, i, rnd.next(1, wScale));
    } else if (treeType == 1) {
        // star
        for (int i = 2; i <= N; i++)
            eds.emplace_back(1, i, rnd.next(1, wScale));
    } else if (treeType == 2) {
        // pure random
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            eds.emplace_back(p, i, rnd.next(1, wScale));
        }
    } else {
        // roughly balanced (attach to lower half)
        for (int i = 2; i <= N; i++) {
            int hi = max(1, (i-1)/2);
            int p = rnd.next(1, hi);
            eds.emplace_back(p, i, rnd.next(1, wScale));
        }
    }

    // Build adjacency for query generation
    vector<vector<int>> adj(N+1);
    for (auto &t : eds) {
        int u, v, w;
        tie(u, v, w) = t;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Shuffle edge order for output
    shuffle(eds.begin(), eds.end());

    // Prepare edge list (without weights) and leaf list
    vector<pair<int,int>> edgeList;
    for (auto &t : eds) {
        int u, v, w;
        tie(u, v, w) = t;
        edgeList.emplace_back(u, v);
    }
    vector<int> leaves;
    for (int i = 1; i <= N; i++)
        if (adj[i].size() == 1)
            leaves.push_back(i);

    // Number of queries
    int maxPairs = N*(N-1)/2;
    int K = rnd.next(1, min(20, maxPairs));

    // Generate diverse queries
    set<pair<int,int>> qs;
    while ((int)qs.size() < K) {
        int t = rnd.next(0, 9), u, v;
        if (t < 2) {
            // adjacent nodes
            auto e = rnd.any(edgeList);
            u = e.first; v = e.second;
        } else if (t < 4) {
            // two leaves
            u = rnd.any(leaves);
            do { v = rnd.any(leaves); } while (v == u);
        } else {
            // completely random pair
            u = rnd.next(1, N);
            do { v = rnd.next(1, N); } while (v == u);
        }
        int a = min(u, v), b = max(u, v);
        qs.emplace(a, b);
    }

    // Output
    println(N);
    for (auto &t : eds) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    println((int)qs.size());
    for (auto &p : qs) {
        println(p.first, p.second);
    }

    return 0;
}
