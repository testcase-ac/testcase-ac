#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+1;
vector<int> adj[MX], child[MX];
int val[MX], ccnt[MX], par[MX], nxt[MX];
void dfs(int i, int p) {
    par[i] = p;
    for(int a: adj[i]) {
        if(a == p) continue;
        child[i].push_back(a);
        dfs(a, i);
    }
}
void update(int i, int v) {
    if(!v) return;
    if(v > val[i]) {
        int remain = v - val[i];
        val[i] *= 2;
        for(int a: child[i]) {
            update(a, remain / child[i].size());
        }
    } else {
        val[i] += v;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    for(int i=0; i<N-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1; i<=N; i++) {
        cin >> val[i];
    }
    dfs(1, 0);
    for(int q=0; q<Q; q++) {
        int t, u, x;
        cin >> t >> u;
        if(t == 1) {
            cin >> x;
            update(u, x);
        } else {
            cout << val[u] << '\n';
        }
    }
}
