#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of servers
    int n = rnd.next(2, 12);

    // Decide whether to ensure at least one path from 1 to n
    bool ensurePath = rnd.next(0, 1);

    vector<pair<int,int>> pathEdges;
    vector<vector<bool>> used(n+1, vector<bool>(n+1, false));
    if (ensurePath) {
        // build a random simple path of length >=1 from 1 to n
        int pathLen = rnd.next(1, n - 1);
        vector<int> nodes;
        nodes.push_back(1);
        if (pathLen > 1) {
            // pick pathLen-1 distinct intermediates from [2..n-1]
            vector<int> mid;
            for (int i = 2; i < n; i++) mid.push_back(i);
            shuffle(mid.begin(), mid.end());
            for (int i = 0; i < pathLen - 1; i++) {
                nodes.push_back(mid[i]);
            }
        }
        nodes.push_back(n);
        for (int i = 0; i + 1 < (int)nodes.size(); i++) {
            int u = nodes[i], v = nodes[i+1];
            pathEdges.emplace_back(u, v);
            used[u][v] = true;
        }
    }

    // collect all other possible directed edges (no self loops, no duplicates)
    vector<pair<int,int>> cand;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && !used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());

    // choose number of extra edges with weighted randomness
    int tot = (int)cand.size();
    int weight = rnd.next(-2, 2);
    int extra = rnd.wnext(tot + 1, weight);

    // form final edge list
    vector<pair<int,int>> edges = pathEdges;
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }
    // shuffle final edges to hide any structure
    shuffle(edges.begin(), edges.end());

    // output
    println(n, edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
