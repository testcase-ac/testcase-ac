#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of parts
    int N = rnd.next(3, 10);
    // Decide how many intermediates among [1..N-1]
    int midCount;
    if (rnd.next(0,1) == 0) {
        midCount = rnd.next(1, N-2);
    } else {
        midCount = rnd.wnext(N-1, -1);
        if (midCount < 1) midCount = 1;
        if (midCount > N-2) midCount = N-2;
    }
    // Shuffle IDs 1..N-1 and split into basics and mids
    vector<int> ids(N-1);
    iota(ids.begin(), ids.end(), 1);
    shuffle(ids.begin(), ids.end());
    vector<int> mids(ids.begin(), ids.begin() + midCount);
    vector<int> basics(ids.begin() + midCount, ids.end());
    // Build a topological order: basics, then mids, then final N
    vector<int> topo;
    topo.insert(topo.end(), basics.begin(), basics.end());
    shuffle(mids.begin(), mids.end());
    topo.insert(topo.end(), mids.begin(), mids.end());
    topo.push_back(N);
    // Hyper-parameter for max dependencies per component (>=2)
    int degMax;
    if (rnd.next(0,1) == 0) {
        degMax = rnd.next(2, N-1);
    } else {
        degMax = rnd.wnext(N-1, 1) + 1;
        if (degMax < 2) degMax = 2;
        if (degMax > N-1) degMax = N-1;
    }
    // Hyper-parameter for max K per dependency
    int Kmax = (rnd.next(0,1) == 0 ? 5 : rnd.next(1, 10));
    // Map node to its position in topo
    vector<int> pos(N+1);
    for (int i = 0; i < (int)topo.size(); i++) {
        pos[topo[i]] = i;
    }
    // Collect edges (X, Y, K)
    vector<tuple<int,int,int>> edges;
    // For each intermediate, pick deps from earlier nodes
    for (int u : mids) {
        int idx = pos[u];
        int avail = idx; // how many earlier nodes
        int maxd = min(degMax, avail);
        int cnt = rnd.next(1, maxd);
        vector<int> cand(topo.begin(), topo.begin() + idx);
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < cnt; i++) {
            int v = cand[i];
            int k = rnd.next(1, Kmax);
            edges.emplace_back(u, v, k);
        }
    }
    // For final product N, pick at least 2 deps
    {
        int idx = pos[N];
        int avail = idx;
        int maxd = min(degMax, avail);
        int cnt = rnd.next(2, maxd);
        vector<int> cand(topo.begin(), topo.begin() + idx);
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < cnt; i++) {
            int v = cand[i];
            int k = rnd.next(1, Kmax);
            edges.emplace_back(N, v, k);
        }
    }

    // --- NEW: ensure every node 1..N-1 has indegree >= 1 ---
    {
        vector<int> indeg(N+1, 0);
        for (auto &e : edges) {
            int x, y, k;
            tie(x, y, k) = e;
            indeg[y]++;
        }
        for (int v = 1; v <= N-1; ++v) {
            if (indeg[v] == 0) {
                int k = rnd.next(1, Kmax);
                edges.emplace_back(N, v, k); // N depends on v
            }
        }
    }
    // --------------------------------------------------------

    // Shuffle edges to randomize order
    shuffle(edges.begin(), edges.end());
    // Output
    println(N);
    println((int)edges.size());
    for (auto &e : edges) {
        int x, y, k;
        tie(x, y, k) = e;
        println(x, y, k);
    }
    return 0;
}
