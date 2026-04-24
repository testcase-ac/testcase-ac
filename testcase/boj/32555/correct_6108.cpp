#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
struct Edge{
    int u, v, w, cap, flow;
};
const int INF = 0x3f3f3f3f;
struct MCMF {
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> par, dist, inque;
    MCMF(int _n) {
        n = _n;
        adj.resize(n+1);
        par.resize(n+1);
        dist.resize(n+1);
        inque.resize(n+1);
    }
    void addedge(int u, int v, int cap, int w) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, w, cap, 0});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, -w, cap, cap});
    }
    void spfa(int src) {
        fill(par.begin(), par.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(inque.begin(), inque.end(), 0);
        dist[src] = 0;
        queue<int> que({src});
        while(que.size()) {
            int q = que.front();
            que.pop();
            inque[q] = 0;
            for(int i: adj[q]) {
                Edge& e = edges[i];
                if(e.flow < e.cap && dist[e.v] > dist[e.u]+e.w) {
                    dist[e.v] = dist[e.u]+e.w;
                    par[e.v] = i;
                    if(!inque[e.v]) {
                        inque[e.v] = 1;
                        que.push(e.v);
                    }
                }
            }
        }
    }
    pair<int, int> solve(int src, int sink) {
        int mc = 0, mf = 0;
        while(1) {
            spfa(src);
            if(par[sink] == -1)
                return {mc, mf};
            int flow = INF, c = sink;
            while(c != src) {
                Edge &e = edges[par[c]];
                flow = min(flow, e.cap-e.flow);
                c = e.u;
            }
            c = sink;
            while(c != src) {
                Edge &e = edges[par[c]], &ie = edges[par[c]^1];
                e.flow += flow;
                ie.flow -= flow;
                c = e.u;
            }
            mf += flow;
            mc += dist[sink]*flow;
        }
    }
};


int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C, S;
    cin >> R >> C;
    vector<string> arr(R);
    for(auto &r: arr) cin >> r;
    cin >> S;
    int row_ycnt = 0;
    vector<int> col_ycnt(C);
    for(int i=0; i<C; i++) {
        if(arr[0][i] == 'Y')
            row_ycnt++;
    }
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            if(arr[i][j] == 'Y')
                col_ycnt[j]++;
        }
    }
    // // printf("row_ycnt = %d\n", row_ycnt);
    for(int c=0; c<C; c++) {
        int ycnt = 0;
        for(int r=0; r<R; r++) {
            if(arr[r][c] == 'Y') {
                ycnt++;
            }
        }
        // // printf("col ycnt = %d\n", ycnt);
        if(ycnt > row_ycnt) {
            return !(cout << "Bugged!");
        }
    }
    int req = C + (C - row_ycnt) * R;
    if(req > S)
        return !(cout << "Bugged!");
    vector<vector<int>> ans(R+1, vector<int>(C));
    vector<int> col_idx(C);
    iota(all(col_idx), 0);
    sort(all(col_idx), [&](int a, int b){return col_ycnt[a] < col_ycnt[b];});
    arr.push_back(string(C, 'G'));
    for(int i=0; i<row_ycnt; i++) {
        // printf("index %d set to Y\n", col_idx[i]);
        arr[R][col_idx[i]] = 'Y';
        col_ycnt[col_idx[i]]++;
    }
    for(int d=row_ycnt; d>0; d--) {
        MCMF mcmf(R+C+4);
        // printf("at d = %d--------\n", d);
        vector<tuple<int, int, int>> edgerec;
        for(int r=0; r<=R; r++) {
            for(int c=0; c<C; c++) {
                if(arr[r][c] == 'Y') {
                    // printf("make edge %d %d\n", r, c);
                    edgerec.push_back({r, c, mcmf.edges.size()});
                    mcmf.addedge(r, R+1+c, 1, 0);
                }
            }
        }
        for(int r=0; r<=R; r++) {
            mcmf.addedge(R+C+2, r, 1, 0);
        }
        for(int c=0; c<C; c++) {
            mcmf.addedge(R+1+c, R+C+3, 1, (col_ycnt[c] == d) ? -1 : 0);
        }
        
        auto [mc, mf] = mcmf.solve(R+C+2, R+C+3);
        // printf("mc = %d, mf = %d\n", mc, mf);
        for(auto [r, c, eidx]: edgerec) {
            if(mcmf.edges[eidx].flow) {
                assert(arr[r][c] == 'Y');
                // printf("matched at r = %d, c = %d\n", r , c);
                arr[r][c] = 'G';
                ans[r][c] = row_ycnt+1-d;
                col_ycnt[c]--;
            }
        }
        if(mf != R+1) {
            return !(cout << "Bugged!");
        }
        // // printf("match res at tc = %d: %d\n", tc, res);


    }
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            if(arr[r][c] == 'Y') {
                return !(cout << "Bugged!");
            }
        }
    }
    int nxt = row_ycnt+1;
    for(int r=0; r<=R; r++) {
        for(int c=0; c<C; c++) {
            cout << (ans[r][c] ? ans[r][c] : nxt++) << ' ';
        }
        cout << '\n';
    }
}
