#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of regions
    int N = rnd.next(2, 10);
    // Population bounds hyper-parameter
    int pl = rnd.next(1, 50);
    int ph = rnd.next(pl, 100);
    vector<int> pop(N + 1);
    for (int i = 1; i <= N; i++) {
        pop[i] = rnd.next(pl, ph);
    }

    // Prepare nodes
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);

    // Decide if graph is connected or has multiple components
    bool isConnected = rnd.next(0, 1);
    vector<vector<int>> comps;
    if (isConnected) {
        comps.push_back(nodes);
    } else {
        int maxComp = min(N, 3);
        int compCount = rnd.next(2, maxComp);
        // initial sizes = 1 each
        vector<int> sizes(compCount, 1);
        int rem = N - compCount;
        for (int i = 0; i < rem; i++) {
            sizes[rnd.next(0, compCount - 1)]++;
        }
        shuffle(nodes.begin(), nodes.end());
        int idx = 0;
        for (int c = 0; c < compCount; c++) {
            vector<int> comp;
            for (int j = 0; j < sizes[c]; j++) {
                comp.push_back(nodes[idx++]);
            }
            comps.push_back(comp);
        }
    }

    // Build adjacency with at least a spanning tree in each component
    vector<set<int>> adj(N + 1);
    for (auto &comp : comps) {
        shuffle(comp.begin(), comp.end());
        for (int i = 1; i < (int)comp.size(); i++) {
            int u = comp[i];
            int v = comp[rnd.next(0, i - 1)];
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }

    // Collect possible extra edges within each component
    vector<pair<int,int>> cand;
    for (auto &comp : comps) {
        for (int i = 0; i < (int)comp.size(); i++) {
            for (int j = i + 1; j < (int)comp.size(); j++) {
                int u = comp[i], v = comp[j];
                if (!adj[u].count(v)) {
                    cand.emplace_back(u, v);
                }
            }
        }
    }

    // Hyper-parameter to bias number of extra edges
    vector<int> tChoices = {-1, 0, 1};
    int tExtra = rnd.any(tChoices);
    int maxCand = cand.size();
    int kExtra = 0;
    if (maxCand > 0) {
        kExtra = rnd.wnext(maxCand + 1, tExtra);
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < kExtra; i++) {
        int u = cand[i].first, v = cand[i].second;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    // Output
    println(N);
    // Populations
    for (int i = 1; i <= N; i++) {
        printf("%d%c", pop[i], i == N ? '\n' : ' ');
    }
    // Adjacency lists
    for (int i = 1; i <= N; i++) {
        vector<int> nei(adj[i].begin(), adj[i].end());
        shuffle(nei.begin(), nei.end());
        printf("%d", (int)nei.size());
        for (int v : nei) {
            printf(" %d", v);
        }
        printf("\n");
    }
    return 0;
}
