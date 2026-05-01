#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N small enough for manual check
    int N = rnd.next(5, 30);
    // Hyper: number of components
    int compCount;
    double p = rnd.next();
    if (p < 0.2) {
        compCount = 1;
    } else if (p < 0.6) {
        compCount = rnd.next(2, min(N, 4));
    } else {
        compCount = rnd.next(3, min(N, 6));
    }
    compCount = min(compCount, N);
    // Partition N into compCount positive sizes
    vector<int> sz(compCount, 1);
    int rem = N - compCount;
    while (rem > 0) {
        int i = rnd.next(0, compCount - 1);
        sz[i]++;
        rem--;
    }
    // Assign node indices to components
    vector<vector<int>> comps(compCount);
    int cur = 1;
    for (int i = 0; i < compCount; i++) {
        for (int j = 0; j < sz[i]; j++) {
            comps[i].push_back(cur++);
        }
    }
    // Generate edges: each comp gets a random tree plus extra edges
    set<pair<int,int>> edgeSet;
    for (auto &comp : comps) {
        int s = comp.size();
        // make a random tree
        shuffle(comp.begin(), comp.end());
        for (int i = 1; i < s; i++) {
            int j = rnd.next(0, i - 1);
            int u = comp[i], v = comp[j];
            if (u > v) swap(u, v);
            edgeSet.insert({u, v});
        }
        // extra edges up to s
        int maxExtra = s * (s - 1) / 2 - (s - 1);
        int extra = rnd.next(0, min(maxExtra, s));
        while (extra > 0) {
            int u = rnd.any(comp), v = rnd.any(comp);
            if (u == v) continue;
            if (u > v) swap(u, v);
            if (edgeSet.insert({u, v}).second) {
                extra--;
            }
        }
    }
    // Build edge list
    vector<pair<int,int>> edges(edgeSet.begin(), edgeSet.end());
    int M = edges.size();
    // Hyper: K selection in three regimes
    int K;
    double q = rnd.next();
    if (q < 0.3) {
        K = rnd.next(1, max(1, N / 4));
    } else if (q < 0.7) {
        K = rnd.next(max(1, N / 4), max(1, N / 2));
    } else {
        K = rnd.next(max(1, N / 2), N);
    }
    // Candy values
    int Cmax = rnd.next(10, 20);
    vector<int> candies(N);
    for (int i = 0; i < N; i++) {
        candies[i] = rnd.next(1, Cmax);
    }
    // Output
    println(N, M, K);
    println(candies);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
