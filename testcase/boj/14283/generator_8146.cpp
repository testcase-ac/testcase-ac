#include "testlib.h"
#include <algorithm>
#include <vector>
#include <set>
#include <tuple>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose n: small or medium
    int n;
    if (rnd.next(0, 1)) n = rnd.next(2, 6);
    else n = rnd.next(7, 15);
    int maxEdges = n * (n - 1) / 2;
    // Decide sparse or dense
    bool dense = rnd.next(0, 1);
    int mMin = n - 1;
    int mMax;
    if (dense) {
        mMin = max(mMin, maxEdges / 2);
        mMax = maxEdges;
    } else {
        mMax = min(maxEdges, n - 1 + 3 * n);
    }
    if (mMin > mMax) mMin = mMax;
    int m = rnd.next(mMin, mMax);

    // Generate unique edges ensuring connectivity when all are added
    set<pair<int,int>> used;
    vector<pair<int,int>> edPairs;
    // Build a spanning tree
    for (int i = 2; i <= n; i++) {
        int v = rnd.next(1, i - 1);
        int u = i;
        int a = min(u, v), b = max(u, v);
        used.emplace(a, b);
        edPairs.emplace_back(a, b);
    }
    // Add extra edges
    while ((int)edPairs.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        int a = min(u, v), b = max(u, v);
        if (used.count({a, b})) continue;
        used.emplace(a, b);
        edPairs.emplace_back(a, b);
    }

    // Choose a weight distribution mode
    int weightMode = rnd.next(0, 2);
    vector<tuple<int,int,int>> edges;
    edges.reserve(m);
    for (auto &pr : edPairs) {
        int u = pr.first, v = pr.second;
        int w;
        if (weightMode == 0) {
            // Uniform
            w = rnd.next(1, 100);
        } else if (weightMode == 1) {
            // Skew toward small weights
            w = rnd.wnext(100, -1) + 1;
        } else {
            // Skew toward large weights
            w = rnd.wnext(100, 1) + 1;
        }
        edges.emplace_back(u, v, w);
    }
    shuffle(edges.begin(), edges.end());

    // Choose distinct s and t
    int s = rnd.next(1, n), t = rnd.next(1, n);
    while (t == s) t = rnd.next(1, n);

    // Output
    println(n, m);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    println(s, t);
    return 0;
}
