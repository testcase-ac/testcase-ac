#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for diversity
    double extraEdgeProb = rnd.next();                  // probability to add non-tree edges
    vector<int> biasList = {-2, -1, 0, 1, 2};           
    int weightBias = rnd.any(biasList);                 // bias for 0/1 weights

    // Small graph size
    int N = rnd.next(2, 10);
    // Prepare all possible undirected edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            cand.emplace_back(i, j);
        }
    }

    // Build a random spanning tree to ensure connectivity
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i+1;
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    for (int i = 1; i < N; i++) {
        int u = nodes[i-1], v = nodes[i];
        if (u > v) swap(u, v);
        edges.emplace_back(u, v);
        used.insert({u, v});
    }

    // Add extra edges randomly
    for (auto &e : cand) {
        if ((int)edges.size() >= N*(N-1)/2) break;
        if (used.count(e) == 0 && rnd.next() < extraEdgeProb) {
            edges.push_back(e);
            used.insert(e);
        }
    }

    // Assign weights with bias and shuffle
    vector<tuple<int,int,int>> outEdges;
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int w = rnd.wnext(2, weightBias); // 0 or 1 with bias
        outEdges.emplace_back(u, v, w);
    }
    shuffle(outEdges.begin(), outEdges.end());

    // Choose distinct start and end
    int s = rnd.next(1, N);
    int e = rnd.next(1, N-1);
    if (e >= s) e++;

    // Output
    int M = outEdges.size();
    println(N, M, s, e);
    for (auto &t : outEdges) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    return 0;
}
