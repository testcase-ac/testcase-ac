#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1,0) {
        for(int i=1;i<=n;i++) p[i]=i;
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a, int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
    bool same(int a,int b){ return find(a)==find(b); }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of islands N: bias to small, range 1..10
    int N = rnd.wnext(10, -2) + 1;
    // number of commands Q: bias to small, range 1..20
    int Q = rnd.wnext(20, -3) + 1;
    // initial penguin counts 0..50
    vector<int> peng(N+1);
    for(int i=1;i<=N;i++){
        peng[i] = rnd.next(0, 50);
    }
    // prepare all possible direct bridges (unique unordered pairs)
    vector<pair<int,int>> edgesAvail;
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            edgesAvail.emplace_back(i, j);
        }
    }
    shuffle(edgesAvail.begin(), edgesAvail.end());
    int eidx = 0;

    DSU dsu(N);
    struct Cmd { int type; int a, b; };
    vector<Cmd> cmds;
    cmds.reserve(Q);

    for(int i=0;i<Q;i++){
        double p = rnd.next();
        int t;
        if(N < 2) {
            // only excursion or penguins
            t = (p < 0.5 ? 2 : 1);
        } else {
            if(p < 0.3) t = 0;
            else if(p < 0.6) t = 1;
            else t = 2;
        }
        // if bridge but no edges left, fallback
        if(t == 0 && eidx >= (int)edgesAvail.size()) {
            t = rnd.next(1, 2);
        }
        if(t == 0) {
            // bridge command
            auto e = edgesAvail[eidx++];
            int a = e.first, b = e.second;
            cmds.push_back({0, a, b});
            dsu.unite(a, b);
        } else if(t == 1) {
            // excursion command
            int a = rnd.next(1, N), b = rnd.next(1, N);
            cmds.push_back({1, a, b});
        } else {
            // penguins update
            int a = rnd.next(1, N);
            int x = rnd.next(0, 50);
            cmds.push_back({2, a, x});
            peng[a] = x;
        }
    }

    // output
    println(N);
    // penguin counts
    for(int i=1;i<=N;i++){
        printf("%d", peng[i]);
        if(i < N) printf(" ");
    }
    printf("\n");
    println((int)cmds.size());
    for(auto &c : cmds){
        if(c.type == 0) {
            println("bridge", c.a, c.b);
        } else if(c.type == 1) {
            println("excursion", c.a, c.b);
        } else {
            println("penguins", c.a, c.b);
        }
    }
    return 0;
}
