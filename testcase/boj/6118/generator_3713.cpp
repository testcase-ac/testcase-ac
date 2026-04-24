#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of barns N
    int N = rnd.next(2, 10);
    // Maximum possible edges in undirected simple graph
    int maxEdges = N * (N - 1) / 2;
    // Hyper-parameter: weight for extra edges distribution
    vector<int> wts = {-2, -1, 1, 2};
    int wt = rnd.any(wts);
    // Number of extra edges beyond a tree
    int hiExtra = maxEdges - (N - 1) + 1;
    int extra = rnd.wnext(hiExtra, wt);
    int M = (N - 1) + extra;
    
    // Build a spanning tree with varied shapes
    vector<pair<int,int>> edges;
    double treeType = rnd.next();
    for (int i = 2; i <= N; ++i) {
        int p;
        if (treeType < 0.3) {
            // chain: attach to i-1
            p = i - 1;
        } else if (treeType < 0.6) {
            // star: attach to 1
            p = 1;
        } else {
            // random tree
            p = rnd.next(1, i - 1);
        }
        edges.emplace_back(p, i);
    }
    
    // Mark existing edges to avoid duplicates
    set<pair<int,int>> used;
    for (auto &e : edges) {
        int u = min(e.first, e.second);
        int v = max(e.first, e.second);
        used.insert({u, v});
    }
    
    // Add extra random edges
    while (extra > 0) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (used.count({u, v})) continue;
        used.insert({u, v});
        edges.emplace_back(u, v);
        --extra;
    }
    
    // Shuffle final edge list
    shuffle(edges.begin(), edges.end());
    
    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
