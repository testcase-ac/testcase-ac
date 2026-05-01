#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, c, t;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities (nodes)
    int n = rnd.next(2, 12);
    // Start and end cities
    int s = rnd.next(1, n);
    int e = rnd.next(1, n);
    while (e == s) e = rnd.next(1, n);

    // Hyper-parameters for maximum cost/time
    vector<int> cb = {0, 1, 5, 10, 20, 50, 100};
    int costMax = rnd.any(cb);
    int timeMax = rnd.any(cb);

    // Build all possible simple edges (undirected)
    vector<pair<int,int>> base;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            base.emplace_back(i, j);
        }
    }
    int maxE = (int)base.size();

    vector<Edge> edges;
    // Choose pattern for diversity
    int pat = rnd.next(0, 3);
    if (pat == 0) {
        // Simple chain 1-2,2-3,...,n-1 - n
        for (int i = 1; i < n; i++) {
            int c = rnd.next(0, costMax);
            int t = rnd.next(0, timeMax);
            edges.push_back({i, i+1, c, t});
        }
    }
    else if (pat == 1) {
        // Complete graph
        for (auto &pr : base) {
            int c = rnd.next(0, costMax);
            int t = rnd.next(0, timeMax);
            edges.push_back({pr.first, pr.second, c, t});
        }
    }
    else if (pat == 2) {
        // Random sparse graph
        int m0 = rnd.next(n-1, maxE);
        shuffle(base.begin(), base.end());
        for (int i = 0; i < m0; i++) {
            auto pr = base[i];
            int c = rnd.next(0, costMax);
            int t = rnd.next(0, timeMax);
            edges.push_back({pr.first, pr.second, c, t});
        }
    }
    else {
        // Sparse with parallel edges
        int m0 = rnd.next(n-1, maxE);
        shuffle(base.begin(), base.end());
        vector<pair<int,int>> chosen(base.begin(), base.begin() + m0);
        for (auto &pr : chosen) {
            int c = rnd.next(0, costMax);
            int t = rnd.next(0, timeMax);
            edges.push_back({pr.first, pr.second, c, t});
        }
        int dup = rnd.next(1, min(n, m0));
        for (int i = 0; i < dup; i++) {
            auto pr = rnd.any(chosen);
            int c = rnd.next(0, costMax);
            int t = rnd.next(0, timeMax);
            edges.push_back({pr.first, pr.second, c, t});
        }
    }

    // Shuffle final edge order
    shuffle(edges.begin(), edges.end());
    int m = (int)edges.size();

    // Output the test case
    println(n, m, s, e);
    for (auto &ed : edges) {
        println(ed.u, ed.v, ed.c, ed.t);
    }
    return 0;
}
