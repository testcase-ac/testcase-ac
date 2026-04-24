#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rooms
    int n = rnd.next(3, 10);

    // Choose cycle size k between 2 and min(n-1,4), with some weighting
    int maxCycle = min(n - 1, 4);
    int k = rnd.wnext(maxCycle - 1, rnd.next(-1, 1)) + 2;  // yields [2..maxCycle]

    // Pick k distinct intermediate nodes from 2..n
    vector<int> cand;
    for (int i = 2; i <= n; ++i) cand.push_back(i);
    shuffle(cand.begin(), cand.end());
    vector<int> cycleNodes(cand.begin(), cand.begin() + k);

    // Build a simple cycle 1 -> ... -> nodes -> 1 (undirected edges)
    set<pair<int,int>> used;
    vector<pair<int,int>> edges;
    int u = 1;
    for (int v : cycleNodes) {
        int a = min(u, v), b = max(u, v);
        edges.emplace_back(a, b);
        used.insert({a, b});
        u = v;
    }
    // close the cycle back to 1
    {
        int a = min(u, 1), b = max(u, 1);
        edges.emplace_back(a, b);
        used.insert({a, b});
    }

    // Collect all other possible undirected edges
    vector<pair<int,int>> pool;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!used.count({i, j})) {
                pool.emplace_back(i, j);
            }
        }
    }
    shuffle(pool.begin(), pool.end());

    // Add a small random number of extra edges
    int hiExtra = min((int)pool.size(), n) + 1; // hiExtra>=1
    int extra = rnd.wnext(hiExtra, rnd.next(-1, 1)); // in [0..hiExtra-1]
    for (int i = 0; i < extra; ++i) {
        edges.push_back(pool[i]);
        used.insert(pool[i]);
    }

    // Final shuffle and output
    shuffle(edges.begin(), edges.end());
    int m = edges.size();
    println(n, m);

    // Weight limit hyper-parameter
    int wlim = rnd.wnext(20, rnd.next(-1, 1)) + 1; // in [1..20]
    for (auto &pr : edges) {
        int a = pr.first, b = pr.second;
        int c = rnd.next(1, wlim);
        int d = rnd.next(1, wlim);
        println(a, b, c, d);
    }

    return 0;
}
