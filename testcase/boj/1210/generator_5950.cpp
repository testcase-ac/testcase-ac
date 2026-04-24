#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of tollgates
    int n = rnd.next(2, 10);
    // start and end distinct
    int s = rnd.next(1, n), t;
    do { t = rnd.next(1, n); } while (t == s);
    // number of highways, at least a spanning tree
    int maxEdges = n * (n - 1) / 2;
    int m = rnd.next(n - 1, maxEdges);

    // build a random spanning tree to ensure connectivity
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());
    vector<vector<bool>> used(n+1, vector<bool>(n+1, false));
    vector<pair<int,int>> edges;
    for (int i = 1; i < n; ++i) {
        int u = perm[i-1], v = perm[i];
        if (u > v) swap(u, v);
        edges.emplace_back(u, v);
        used[u][v] = used[v][u] = true;
    }
    // add extra random edges
    int extra = m - (n - 1);
    for (int i = 0; i < extra; ++i) {
        int u, v;
        do {
            u = rnd.next(1, n);
            v = rnd.next(1, n);
            if (u > v) swap(u, v);
        } while (u == v || used[u][v]);
        edges.emplace_back(u, v);
        used[u][v] = used[v][u] = true;
    }

    // node capture costs, biased to produce both small and large values
    vector<int> cost(n+1);
    for (int i = 1; i <= n; ++i) {
        int bias = (rnd.next() < 0.5 ? -1 : 1);
        cost[i] = rnd.wnext(20, bias) + 1;  // [1,20], skewed
    }

    // output
    println(n, m);
    println(s, t);
    for (int i = 1; i <= n; ++i) println(cost[i]);
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
