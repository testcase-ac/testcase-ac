#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of nodes
        int n = rnd.next(5, 12);
        // choose special nodes g and h
        int g = rnd.next(1, n);
        int h = rnd.next(1, n);
        while (h == g) h = rnd.next(1, n);
        // build a random tree including edge g-h
        vector<pair<pair<int,int>, int>> edges;
        edges.reserve(n - 1);
        // add g-h edge first
        edges.push_back({{g, h}, rnd.next(1, 10)});
        // other nodes
        vector<int> rest;
        for (int i = 1; i <= n; i++) {
            if (i != g && i != h) rest.push_back(i);
        }
        shuffle(rest.begin(), rest.end());
        vector<int> existent = {g, h};
        for (int u : rest) {
            int v = rnd.any(existent);
            edges.push_back({{u, v}, rnd.next(1, 10)});
            existent.push_back(u);
        }
        int m = (int)edges.size();
        // choose start s
        int s = rnd.next(1, n);

        // Build adjacency without the g-h edge to find components
        vector<vector<int>> adj(n+1);
        for (auto &e : edges) {
            int u = e.first.first, v = e.first.second;
            if ((u == g && v == h) || (u == h && v == g)) continue;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> vis(n+1, false);
        // dfs from s
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int w : adj[u]) if (!vis[w]) dfs(w);
        };
        dfs(s);

        // classify valid and invalid candidates
        vector<int> valid, invalid;
        for (int i = 1; i <= n; i++) {
            if (i == s) continue;
            if (!vis[i]) valid.push_back(i);
            else invalid.push_back(i);
        }
        // candidate count
        int maxCand = min(n-2, 4);
        int t = rnd.next(1, maxCand);
        // we must have at least one valid
        int x0 = rnd.any(valid);
        vector<int> cands;
        cands.push_back(x0);
        int rem = t - 1;
        if (rem > 0) {
            vector<int> pool;
            for (int i = 1; i <= n; i++) {
                if (i == s || i == x0) continue;
                pool.push_back(i);
            }
            shuffle(pool.begin(), pool.end());
            for (int i = 0; i < rem; i++) {
                cands.push_back(pool[i]);
            }
        }
        // output
        println(n, m, t);
        println(s, g, h);
        for (auto &e : edges) {
            int u = e.first.first, v = e.first.second;
            if (u > v) swap(u, v);
            println(u, v, e.second);
        }
        for (int x : cands) {
            println(x);
        }
    }
    return 0;
}
