#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of nodes (at least 2 so we can have M >= 1)
    int N = rnd.next(2, 10);
    // Start and end cities
    int S = rnd.next(1, N);
    int T = rnd.next(1, N);

    // Prepare matrix to mark used edges
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    vector<pair<int,int>> edges;

    // Whether to ensure at least one simple path from S to T
    bool ensurePath = rnd.next(0, 1) == 1;

    if (ensurePath && S != T) {
        // Build a simple path S -> ... -> T
        int midCount = 0;
        if (N >= 3) {
            midCount = rnd.next(1, N - 2);
        }
        vector<int> cand;
        for (int i = 1; i <= N; i++) {
            if (i != S && i != T) cand.push_back(i);
        }
        shuffle(cand.begin(), cand.end());
        vector<int> path;
        path.push_back(S);
        for (int i = 0; i < midCount; i++) {
            path.push_back(cand[i]);
        }
        path.push_back(T);
        for (int i = 0; i + 1 < (int)path.size(); i++) {
            int u = path[i], v = path[i+1];
            edges.emplace_back(u, v);
            used[u][v] = true;
        }
    }

    // All possible directed edges (i != j)
    vector<pair<int,int>> allPairs;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i != j) allPairs.emplace_back(i, j);
        }
    }
    shuffle(allPairs.begin(), allPairs.end());

    int maxEdges = N * (N - 1);
    int M;
    if (ensurePath && S != T) {
        int pathEdges = edges.size();
        // Keep at least the path edges, up to all possible edges
        M = rnd.next(pathEdges, maxEdges);
    } else {
        // Ensure at least one edge
        int w = rnd.any(vector<int>{-1, 0, 1});
        // rnd.wnext(maxEdges, w) yields [0, maxEdges-1], so +1 gives [1, maxEdges]
        M = rnd.wnext(maxEdges, w) + 1;
    }

    // Fill edges up to M
    for (auto &p : allPairs) {
        if ((int)edges.size() >= M) break;
        int u = p.first, v = p.second;
        if (!used[u][v]) {
            used[u][v] = true;
            edges.emplace_back(u, v);
        }
    }

    // Output the test case
    println(N, M, S, T);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
