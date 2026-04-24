#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 5);
    // weight-bias parameters for diversity
    vector<int> tparams = {-2, -1, 0, 1, 2};

    for (int ti = 0; ti < T; ti++) {
        // number of nodes
        int n = rnd.next(3, 10);
        // prepare internal node pool
        vector<int> nodes;
        for (int i = 2; i <= n - 1; i++)
            nodes.push_back(i);
        shuffle(nodes.begin(), nodes.end());

        // decide numbers of internal nodes for two disjoint paths
        int maxInternal = n - 2;
        int k1 = rnd.next(0, maxInternal);
        int k2 = rnd.next(0, maxInternal - k1);
        // avoid both paths being direct (would create only one edge)
        if (k1 + k2 == 0) {
            if (rnd.next(0, 1) == 0) k1 = 1;
            else k2 = 1;
        }

        // build the two vertex-disjoint paths from 1 to n
        vector<int> path1, path2;
        path1.push_back(1);
        for (int i = 0; i < k1; i++)
            path1.push_back(nodes[i]);
        path1.push_back(n);

        path2.push_back(1);
        for (int i = 0; i < k2; i++)
            path2.push_back(nodes[k1 + i]);
        path2.push_back(n);

        // collect edges, avoiding duplicates
        set<pair<int,int>> used;
        vector<tuple<int,int,int>> edges;

        // helper to add an edge with random weight
        auto addEdge = [&](int u, int v) {
            int t = rnd.any(tparams);
            int w = rnd.wnext(100, t) + 1;  // weight in [1,100], biased
            edges.emplace_back(u, v, w);
            used.insert({u, v});
        };

        // add edges from path1
        for (int i = 0; i + 1 < (int)path1.size(); i++) {
            int u = path1[i], v = path1[i + 1];
            addEdge(u, v);
        }
        // add edges from path2
        for (int i = 0; i + 1 < (int)path2.size(); i++) {
            int u = path2[i], v = path2[i + 1];
            if (!used.count({u, v}))
                addEdge(u, v);
        }

        // prepare candidate extra edges (u != v, not already used)
        vector<pair<int,int>> cand;
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                if (u != v && !used.count({u, v}))
                    cand.emplace_back(u, v);
            }
        }
        shuffle(cand.begin(), cand.end());

        // add a random number of extra edges for complexity
        int extraMax = cand.size();
        int extra = rnd.next(0, min(extraMax, n));
        for (int i = 0; i < extra; i++) {
            int u = cand[i].first, v = cand[i].second;
            addEdge(u, v);
        }

        // output this test case
        int M = edges.size();
        println(n, M);
        for (auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            println(u, v, w);
        }
    }
    return 0;
}
