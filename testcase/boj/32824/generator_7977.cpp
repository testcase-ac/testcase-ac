#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Edge { int u, v, w; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cities
    int n = rnd.next(2, 10);
    // Maximum possible edges
    int maxE = n * (n - 1) / 2;
    int minE = n - 1;
    int maxExtra = maxE - minE;
    // Hyper-parameter to skew extra edges distribution
    vector<int> ts = { -1, 0, 1 };
    int t2 = rnd.any(ts);
    // extra in [0, maxExtra], possibly skewed
    int extra = rnd.wnext(maxExtra + 1, t2);
    int m = minE + extra;

    // Build a random spanning tree to ensure connectivity
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());
    vector<vector<bool>> used(n+1, vector<bool>(n+1, false));
    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 1; i < n; i++) {
        int u = perm[i], v = perm[rnd.next(0, i-1)];
        if (u > v) swap(u, v);
        used[u][v] = used[v][u] = true;
        edges.push_back({u, v, 0});
    }
    // List remaining possible edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!used[i][j]) cand.emplace_back(i, j);
        }
    }
    shuffle(cand.begin(), cand.end());
    // Add extra edges
    for (int i = 0; i < extra; i++) {
        edges.push_back({cand[i].first, cand[i].second, 0});
    }

    // Hyper-parameter: cost distribution skew
    int t1 = rnd.any(ts);
    // Hyper-parameter: max cost choice
    vector<int> capc = {10, 20, 50};
    int Cmax = rnd.any(capc);

    // Assign costs
    for (auto &e : edges) {
        e.w = rnd.wnext(Cmax, t1) + 1;  // costs in [1, Cmax]
    }
    // Shuffle input order
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, m);
    for (auto &e : edges) {
        println(e.u, e.v, e.w);
    }
    return 0;
}
