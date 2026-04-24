#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct DSU {
    int n;
    vector<int> p;
    vector<long long> diff; // diff[x] = weight[x] - weight[parent[x]]
    DSU(int _n): n(_n), p(n+1), diff(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        int par = p[x];
        int r = find(par);
        diff[x] += diff[par];
        return p[x] = r;
    }
    // enforce: weight[v] - weight[u] = w
    bool unite(int u, int v, long long w) {
        int ru = find(u);
        int rv = find(v);
        if (ru == rv) return false;
        long long du = diff[u];
        long long dv = diff[v];
        // After union, attach rv -> ru
        // We need: (weight[rv] + dv) - (weight[ru] + du) = w
        // => weight[rv] - weight[ru] = w + du - dv
        long long val = w + du - dv;
        p[rv] = ru;
        diff[rv] = val;
        return true;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    long long between(int u, int v) {
        // weight[v] - weight[u]
        find(u); find(v);
        return diff[v] - diff[u];
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 3);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(2, 10);
        int M = rnd.next(1, 20);
        println(N, M);
        // underlying true weights for consistency
        vector<long long> W(N+1);
        for (int i = 1; i <= N; i++) {
            W[i] = rnd.next(0, 1000);
        }
        DSU dsu(N);
        double pMeas = rnd.next(0.0, 1.0);
        for (int i = 0; i < M; i++) {
            bool doMeas = rnd.next() < pMeas;
            if (doMeas) {
                int u = rnd.next(1, N), v = rnd.next(1, N);
                while (v == u) v = rnd.next(1, N);
                long long w = llabs(W[v] - W[u]);
                if (W[v] >= W[u]) {
                    println("!", u, v, w);
                    dsu.unite(u, v, w);
                } else {
                    println("!", v, u, w);
                    dsu.unite(v, u, w);
                }
            } else {
                int u = rnd.next(1, N), v = rnd.next(1, N);
                while (v == u) v = rnd.next(1, N);
                println("?", u, v);
            }
        }
    }
    // end marker
    println(0, 0);
    return 0;
}
