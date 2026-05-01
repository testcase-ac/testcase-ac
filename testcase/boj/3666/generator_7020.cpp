#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 15);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(2, 15);
        // choose owned count
        int k = rnd.next(1, n - 1);
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        vector<bool> owned(n, false);
        for (int i = 0; i < k; i++) owned[idx[i]] = true;
        // armies
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            if (owned[i]) a[i] = rnd.next(1, 10);
            else a[i] = 0;
        }
        // adjacency
        vector<vector<char>> adj(n, vector<char>(n, 'N'));
        double p_oo = rnd.next() * 0.5 + 0.5;  // [0.5,1)
        double p_ee = rnd.next() * 0.3;        // [0,0.3)
        double p_oe = rnd.next() * 0.8 + 0.1;  // [0.1,0.9)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool o1 = owned[i], o2 = owned[j];
                bool edge = false;
                if (o1 && o2) {
                    edge = rnd.next() < p_oo;
                } else if (!o1 && !o2) {
                    edge = rnd.next() < p_ee;
                } else {
                    edge = rnd.next() < p_oe;
                }
                if (edge) {
                    adj[i][j] = adj[j][i] = 'Y';
                }
            }
        }
        // ensure at least one owned-enemy edge
        bool hasOE = false;
        for (int i = 0; i < n && !hasOE; i++) {
            if (!owned[i]) continue;
            for (int j = 0; j < n; j++) {
                if (!owned[j]) continue;
                // skip
            }
        }
        for (int i = 0; i < n && !hasOE; i++) {
            if (!owned[i]) continue;
            for (int j = 0; j < n; j++) {
                if (owned[j]) continue;
                if (adj[i][j] == 'Y') {
                    hasOE = true;
                    break;
                }
            }
        }
        if (!hasOE) {
            // pick one owned and one enemy
            vector<int> os, es;
            for (int i = 0; i < n; i++) {
                if (owned[i]) os.push_back(i);
                else es.push_back(i);
            }
            int u = rnd.any(os), v = rnd.any(es);
            adj[u][v] = adj[v][u] = 'Y';
        }
        // sometimes force connected owned subgraph
        if (k > 1 && rnd.next() < 0.5) {
            vector<int> os;
            for (int i = 0; i < n; i++) if (owned[i]) os.push_back(i);
            shuffle(os.begin(), os.end());
            for (int i = 1; i < (int)os.size(); i++) {
                int j = rnd.next(0, i - 1);
                int u = os[i], v = os[j];
                adj[u][v] = adj[v][u] = 'Y';
            }
        }
        // output
        println(n);
        println(a);
        for (int i = 0; i < n; i++) {
            string s(n, 'N');
            for (int j = 0; j < n; j++) s[j] = adj[i][j];
            println(s);
        }
    }
    return 0;
}
