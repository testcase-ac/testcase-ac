#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample N between 2 and ~14 with bias
    int tSignN = rnd.any(vector<int>{-1, 0, 1});
    int N = rnd.wnext(13, tSignN) + 2;
    // Build a random topological order with 1 as start and N as end
    vector<int> mids;
    for (int i = 2; i < N; i++) mids.push_back(i);
    shuffle(mids.begin(), mids.end());
    vector<int> ord;
    ord.push_back(1);
    for (int x : mids) ord.push_back(x);
    ord.push_back(N);
    // Base edges to ensure connectivity
    vector<pair<int,int>> edges;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (int i = 1; i < N; i++) {
        int u = ord[i-1], v = ord[i];
        edges.emplace_back(u, v);
        used[u][v] = true;
    }
    // Candidate extra edges (u->v) respecting topo order
    vector<pair<int,int>> cand;
    vector<int> pos(N+1);
    for (int i = 0; i < N; i++) pos[ord[i]] = i;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (pos[i] < pos[j] && !used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    int extraMax = cand.size();
    int extra = rnd.next(0, min(extraMax, N));
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }
    int M = edges.size();
    // K between 0 and min(N-2,3)
    int K = rnd.next(0, min(N-2, 3));
    // Choose a time upper bound
    vector<int> UB = {10, 20, 50, 100, 1000};
    int T = rnd.any(UB);
    // Generate execution times
    vector<int> times(N);
    for (int i = 0; i < N; i++) {
        times[i] = rnd.next(1, T);
    }
    // Output
    println(N, M, K);
    println(times);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
