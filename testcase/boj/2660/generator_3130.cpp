#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of members between 2 and 10
    int N = rnd.next(2, 10);

    // Generate a random spanning tree to ensure connectivity
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    vector<pair<int,int>> treeEdges;
    for (int i = 1; i < N; ++i) {
        int j = rnd.next(0, i - 1);
        treeEdges.emplace_back(perm[i], perm[j]);
    }

    // Build all possible undirected edges (i<j)
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            allEdges.emplace_back(i, j);

    // Normalize tree edges into a set for quick exclusion
    set<pair<int,int>> treeSet;
    vector<pair<int,int>> treeNorm;
    for (auto &e : treeEdges) {
        int u = min(e.first, e.second);
        int v = max(e.first, e.second);
        treeNorm.emplace_back(u, v);
        treeSet.insert({u, v});
    }

    // Collect extra edges not in the tree
    vector<pair<int,int>> extra;
    for (auto &e : allEdges) {
        if (!treeSet.count(e))
            extra.push_back(e);
    }

    // Hyper-parameter to bias number of extra edges
    int totalEdges = N * (N - 1) / 2;
    int remaining = totalEdges - (N - 1);
    int t = rnd.next(-2, 2);
    int K = rnd.wnext(remaining + 1, t);  // number of extra edges to add

    shuffle(extra.begin(), extra.end());
    vector<pair<int,int>> edges = treeNorm;
    for (int i = 0; i < K; ++i)
        edges.push_back(extra[i]);

    // Shuffle the final edge list
    shuffle(edges.begin(), edges.end());

    // Randomly swap endpoints for additional diversity
    double pSwap = rnd.next(0.0, 1.0);
    for (auto &e : edges)
        if (rnd.next() < pSwap)
            swap(e.first, e.second);

    // Output in the required format
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);
    println(-1, -1);

    return 0;
}
