#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small size
    int N = rnd.next(1, 10);
    // decide number of cycles
    int maxCycles = N / 3;
    int numCycles = rnd.next(0, maxCycles);

    // prepare node labels and shuffle them
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    vector<int> used;
    used.push_back(nodes[0]);
    int pos = 1;

    // store edges and paths
    vector<pair<int,int>> edges;
    vector<vector<int>> cyclePaths, treePaths;

    while (pos < N) {
        bool canCycle = (numCycles > 0 && pos + 2 <= N);
        if (canCycle && rnd.next(0,1) == 1) {
            // create a cycle: one used node + x new nodes, x>=2
            int maxNew = N - pos;
            int x = rnd.next(2, maxNew);
            int u = rnd.any(used);
            vector<int> newNodes;
            for (int i = 0; i < x; i++) {
                newNodes.push_back(nodes[pos + i]);
            }
            // build cycle path
            vector<int> p;
            p.push_back(u);
            for (int v : newNodes) p.push_back(v);
            p.push_back(u);
            // record edges
            int prev = u;
            for (int v : newNodes) {
                edges.emplace_back(prev, v);
                prev = v;
            }
            edges.emplace_back(prev, u);
            // mark new nodes used
            for (int v : newNodes) used.push_back(v);
            pos += x;
            numCycles--;
            cyclePaths.push_back(p);
        } else {
            // tree edge
            int u = rnd.any(used);
            int v = nodes[pos];
            edges.emplace_back(u, v);
            used.push_back(v);
            treePaths.push_back({u, v});
            pos++;
        }
    }

    // combine paths and shuffle order
    vector<vector<int>> paths;
    for (auto &p : cyclePaths) paths.push_back(p);
    for (auto &p : treePaths) paths.push_back(p);
    shuffle(paths.begin(), paths.end());

    int M = (int)paths.size();
    // output
    println(N, M);
    for (auto &p : paths) {
        printf("%d", (int)p.size());
        for (int v : p) printf(" %d", v);
        printf("\n");
    }

    return 0;
}
