#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(3, 10);

    // Track which nodes are already in cycles
    vector<bool> used(N+1, false);
    vector<vector<int>> cycles;
    int remaining = N;

    // Generate 1+ random cycles of size 2..4 until we run out or stop by coin flip
    while (remaining >= 2 && (cycles.empty() || rnd.next(0,1) == 0)) {
        int maxk = min(remaining, 4);
        int k = rnd.next(2, maxk);
        // collect unused nodes
        vector<int> cur;
        for (int i = 1; i <= N; i++) if (!used[i]) cur.push_back(i);
        shuffle(cur.begin(), cur.end());
        vector<int> cyc;
        for (int i = 0; i < k; i++) {
            cyc.push_back(cur[i]);
            used[cur[i]] = true;
        }
        cycles.push_back(cyc);
        remaining -= k;
    }

    // Any leftover nodes become tree attachments
    vector<int> leftover;
    for (int i = 1; i <= N; i++) if (!used[i]) leftover.push_back(i);

    // Build the accusation array
    vector<int> accuse(N+1, 0);

    // Make each cycle a directed cycle
    for (auto &cyc : cycles) {
        int k = cyc.size();
        for (int i = 0; i < k; i++) {
            int u = cyc[i];
            int v = cyc[(i+1) % k];
            accuse[u] = v;
        }
    }

    // Prepare pool of possible parents (all cycle nodes)
    vector<int> parentPool;
    for (auto &cyc : cycles)
        for (int u : cyc)
            parentPool.push_back(u);

    // Randomize order of leftover attachments
    shuffle(leftover.begin(), leftover.end());
    for (int u : leftover) {
        // attach to a random existing node
        int p = rnd.any(parentPool);
        accuse[u] = p;
        parentPool.push_back(u);
    }

    // Finally, permute labels to hide structure
    vector<int> p(N+1);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin() + 1, p.end());
    vector<int> outAcc(N+1);
    for (int i = 1; i <= N; i++) {
        outAcc[p[i]] = p[accuse[i]];
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        println(outAcc[i]);
    }
    return 0;
}
