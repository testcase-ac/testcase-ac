#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5 + 2;
vector<int> adj[MX];
int par[MX], nxt[MX], prv[MX];
void dfs(int i) {
    for(int j : adj[i]) {
        if(j != par[i]) {
            par[j] = i;
            dfs(j);
        }
    }
}
int N, S, T;
vector<int> ans;
void construct(int t, bool fst, int p = -1) {
    if(fst) {
        ans.push_back(t);
    }
    for(int a: adj[t]) {
        if(a != prv[t] && a != nxt[t] && a != p) {
            construct(a, !fst, t);
        }
    }
    if(!fst) {
        ans.push_back(t);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=0; i<N-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> S >> T;
    dfs(S);
    vector<int> par_v;
    for(int i=T; i!=S; i=par[i]) {
        par_v.push_back(i);
    }
    par_v.push_back(S);
    reverse(par_v.begin(), par_v.end());
    for(int i=0; i<par_v.size()-1; i++) {
        nxt[par_v[i]] = par_v[i+1];
    }
    for(int i=1; i<par_v.size(); i++) {
        prv[par_v[i]] = par_v[i-1];
    }
    for(int i=0; i<par_v.size() - 1; i++) {
        construct(par_v[i], true);
    }
    construct(T, false);
    for(int t: ans) {
        cout << t << '\n';
    }
}
