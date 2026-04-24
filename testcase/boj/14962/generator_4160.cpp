#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of people (countries)
    int p = rnd.next(1, 3);
    println(p);

    for (int person = 0; person < p; person++) {
        // Number of cities: 2 to 10
        int n = rnd.next(2, 10);
        // Number of roads: between n-1 and min(4*n, n*(n-1))
        int maxM = min(4 * n, n * (n - 1));
        int m = rnd.next(n - 1, maxM);

        // Generate hotel costs with some variety
        vector<int> h(n + 1);
        for (int i = 1; i <= n; i++) {
            double r = rnd.next();
            if (r < 0.2) {
                h[i] = 0;
            } else if (r < 0.7) {
                h[i] = rnd.next(1, 10);
            } else if (r < 0.9) {
                h[i] = rnd.next(10, 100);
            } else {
                h[i] = rnd.next(100, 1000);
            }
        }

        // Build a directed spanning tree from city 1 to ensure reachability
        set<pair<int,int>> used;
        vector<tuple<int,int,int>> edges;
        for (int v = 2; v <= n; v++) {
            int u = rnd.next(1, v - 1);
            int w = (rnd.next() < 0.7 ? rnd.next(1, 10) : rnd.next(10, 100));
            edges.emplace_back(u, v, w);
            used.insert({u, v});
        }
        // Add random extra edges until we have m edges
        while ((int)edges.size() < m) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v || used.count({u, v})) continue;
            int w = (rnd.next() < 0.7 ? rnd.next(1, 10) : rnd.next(10, 100));
            edges.emplace_back(u, v, w);
            used.insert({u, v});
        }

        // Output this country's data
        println(n, m);
        // print hotel costs each on its own line
        for (int i = 1; i <= n; i++) {
            println(h[i]);
        }
        // print edges
        for (auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            println(u, v, w);
        }
        // Choose an airport city
        int a = rnd.next(1, n);
        println(a);
    }

    return 0;
}
