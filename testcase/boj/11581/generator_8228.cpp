#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of intersections
    int N = rnd.next(1, 10);
    // Mode: 0 = guaranteed acyclic, 1 = random, 2 = enforce a reachable cycle (only if N>=3)
    int mode = rnd.next(0, N >= 3 ? 2 : 1);

    vector<vector<int>> adj(N+1);

    if (mode == 0) {
        // Acyclic: only edges i -> j with j > i
        for (int i = 1; i <= N-1; i++) {
            int maxOut = N - i;
            int Mi = rnd.wnext(maxOut + 1, rnd.any(vector<int>{-1,1}));
            vector<int> cand;
            for (int j = i+1; j <= N; j++) cand.push_back(j);
            shuffle(cand.begin(), cand.end());
            cand.resize(Mi);
            adj[i] = cand;
        }
    } else if (mode == 1) {
        // Fully random (no self-loops)
        for (int i = 1; i <= N-1; i++) {
            int Mi = rnd.wnext(N, rnd.any(vector<int>{-1,2}));
            vector<int> cand;
            for (int j = 1; j <= N; j++) {
                if (j == i) continue; // no self-loop
                cand.push_back(j);
            }
            shuffle(cand.begin(), cand.end());
            adj[i].assign(cand.begin(), cand.begin() + min((int)cand.size(), Mi));
        }
    } else {
        // mode == 2: enforce at least one cycle reachable from 1 (excluding N)
        int maxCycleLen = min(N-1, 5);
        int L = rnd.next(2, maxCycleLen);
        // pick L-1 distinct nodes from [2..N-1]
        vector<int> pool;
        for (int i = 2; i <= N-1; i++) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        vector<int> cycleNodes = {1};
        for (int i = 0; i < L-1; i++) cycleNodes.push_back(pool[i]);
        // form the cycle
        for (int i = 0; i < L; i++) {
            int u = cycleNodes[i];
            int v = cycleNodes[(i+1)%L];
            if (u != v) adj[u].push_back(v);
        }
        // add some extra random edges
        for (int i = 1; i <= N-1; i++) {
            int already = adj[i].size();
            int extra = rnd.wnext(N - already, rnd.any(vector<int>{-1,2}));
            vector<int> cand;
            for (int j = 1; j <= N; j++) {
                if (j == i) continue;
                if (find(adj[i].begin(), adj[i].end(), j) == adj[i].end())
                    cand.push_back(j);
            }
            shuffle(cand.begin(), cand.end());
            for (int k = 0; k < extra && k < (int)cand.size(); k++)
                adj[i].push_back(cand[k]);
        }
    }

    // Output
    println(N);
    for (int i = 1; i <= N-1; i++) {
        int Mi = adj[i].size();
        println(Mi);
        if (Mi > 0) {
            println(adj[i]);
        }
    }
    return 0;
}
