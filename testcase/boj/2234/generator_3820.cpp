#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
    int n;
    vector<int> p;
    DSU(int _n): n(_n), p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b){
        a = find(a); b = find(b);
        if(a != b) p[b] = a;
    }
};

struct Edge {
    int idx, u, v;
    int r, c, nr, nc;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // grid size
    int N = rnd.next(2, 10); // columns
    int M = rnd.next(2, 10); // rows
    int W = N * M;
    // list all adjacent edges
    vector<Edge> edges;
    for(int r = 0; r < M; r++){
        for(int c = 0; c < N; c++){
            int u = r * N + c;
            if(c + 1 < N){
                int nr = r, nc = c + 1;
                int v = nr * N + nc;
                edges.push_back({(int)edges.size(), u, v, r, c, nr, nc});
            }
            if(r + 1 < M){
                int nr = r + 1, nc = c;
                int v = nr * N + nc;
                edges.push_back({(int)edges.size(), u, v, r, c, nr, nc});
            }
        }
    }
    int E = edges.size();
    // choose number of rooms (components) >=2
    int maxK = min(W, 5);
    int K = rnd.next(2, maxK);
    // shuffle cells and partition into K groups
    vector<int> perm(W);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());
    vector<int> gid(W);
    int base = W / K, rem = W % K;
    int ptr = 0;
    for(int g = 0; g < K; g++){
        int sz = base + (g < rem ? 1 : 0);
        for(int i = 0; i < sz; i++){
            gid[perm[ptr++]] = g;
        }
    }
    // collect intra-group edges
    vector<int> intra;
    for(auto &e : edges){
        if(gid[e.u] == gid[e.v]) intra.push_back(e.idx);
    }
    // build spanning forest within each group
    DSU dsu(W);
    vector<bool> openEdge(E, false);
    shuffle(intra.begin(), intra.end());
    for(int idx : intra){
        auto &e = edges[idx];
        if(dsu.find(e.u) != dsu.find(e.v)){
            dsu.unite(e.u, e.v);
            openEdge[idx] = true;
        }
    }
    // extra random openings within group
    double p = rnd.next(1, 9) / 10.0; // 0.1 to 0.9
    for(int idx : intra){
        if(!openEdge[idx] && rnd.next() < p){
            openEdge[idx] = true;
        }
    }
    // build wall masks
    vector<vector<int>> a(M, vector<int>(N, 15));
    for(auto &e : edges){
        if(openEdge[e.idx]){
            int r = e.r, c = e.c, nr = e.nr, nc = e.nc;
            // east-west
            if(r == nr){
                if(c + 1 == nc){
                    a[r][c] &= ~4;  // remove east
                    a[nr][nc] &= ~1; // remove west
                } else {
                    a[r][c] &= ~1;
                    a[nr][nc] &= ~4;
                }
            } else { // north-south
                if(r + 1 == nr){
                    a[r][c] &= ~8;  // remove south
                    a[nr][nc] &= ~2; // remove north
                } else {
                    a[r][c] &= ~2;
                    a[nr][nc] &= ~8;
                }
            }
        }
    }
    // output
    println(N, M);
    for(int r = 0; r < M; r++){
        println(a[r]);
    }
    return 0;
}
