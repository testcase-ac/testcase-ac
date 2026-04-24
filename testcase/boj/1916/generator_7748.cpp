#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of cities
    int N = rnd.next(2, 10);
    // Maximum possible directed edges without self-loops
    int maxEdges = N * (N - 1);
    
    // Hyper-parameter for edge count distribution: bias towards sparse, uniform, or dense
    vector<int> tMList = {-2, 0, 2};
    int tM = rnd.any(tMList);
    // Generate raw M in [0..maxEdges]
    int Mraw = rnd.wnext(maxEdges + 1, tM);
    
    // Choose path length L to guarantee connectivity between start and target
    int Lmax = min({N, 6});
    int L = rnd.next(2, Lmax);
    
    // Build a guaranteed simple path of length L
    vector<int> p(N);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    p.resize(L);
    int start = p.front(), target = p.back();
    
    // Ensure at least L-1 edges to form the path
    int M = max(Mraw, L - 1);
    M = min(M, maxEdges);
    
    // Mark used directed edges to avoid duplicates
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    vector<pair<int,int>> edges;
    for (int i = 0; i + 1 < L; i++) {
        int u = p[i], v = p[i+1];
        used[u][v] = true;
        edges.emplace_back(u, v);
    }
    
    // Collect remaining candidate edges (u != v, not used)
    vector<pair<int,int>> cand;
    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            if (u != v && !used[u][v]) {
                cand.emplace_back(u, v);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    
    // Add remaining edges to reach total M
    int rem = M - (L - 1);
    for (int i = 0; i < rem; i++) {
        edges.push_back(cand[i]);
    }
    shuffle(edges.begin(), edges.end());
    
    // Hyper-parameter for weight distribution: bias towards small, uniform, or large
    vector<int> tWList = {-2, 0, 2};
    int tW = rnd.any(tWList);
    
    // Output according to problem format
    println(N);
    println(M);
    for (auto &e : edges) {
        int w = rnd.wnext(100000, tW); // [0..99999]
        println(e.first, e.second, w);
    }
    println(start, target);
    
    return 0;
}
