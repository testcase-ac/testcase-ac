#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of nodes
        int n = rnd.next(1, 10);
        set<pair<int,int>> edges;
        vector<int> nodes(n);
        for (int i = 0; i < n; i++) nodes[i] = i;

        // Hyper-parameters for adding a cycle
        double pCycle = rnd.next(0.0, 1.0);
        vector<bool> used(n, false);
        if (n >= 2 && rnd.next() < pCycle) {
            int k = rnd.next(2, n);
            shuffle(nodes.begin(), nodes.end());
            vector<int> cyc(nodes.begin(), nodes.begin() + k);
            for (int i = 0; i < k; i++) {
                int u = cyc[i], v = cyc[(i+1)%k];
                edges.insert({u, v});
                used[u] = true;
            }
        }

        // Hyper-parameters for adding a path
        double pPath = rnd.next(0.0, 1.0);
        vector<int> avail;
        for (int i = 0; i < n; i++) if (!used[i]) avail.push_back(i);
        if (!avail.empty() && rnd.next() < pPath) {
            int l = rnd.next(1, (int)avail.size());
            shuffle(avail.begin(), avail.end());
            vector<int> path(avail.begin(), avail.begin() + l);
            for (int i = 0; i+1 < l; i++) {
                edges.insert({path[i], path[i+1]});
            }
        }

        // Decide total edges m
        int pre = edges.size();
        int maxE = min(n * (n - 1), 20);
        int m = pre <= maxE ? rnd.next(pre, maxE) : pre;

        // Fill with random edges
        while ((int)edges.size() < m) {
            int u = rnd.next(0, n-1);
            int v = rnd.next(0, n-1);
            if (u != v) edges.insert({u, v});
        }

        // Output
        vector<pair<int,int>> eds(edges.begin(), edges.end());
        shuffle(eds.begin(), eds.end());
        println(n, m);
        for (auto &e : eds) {
            println(e.first, e.second);
        }
    }
    return 0;
}
