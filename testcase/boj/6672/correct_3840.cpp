#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<int> num, low, isarti;
int ind = 1;
int dfs(int u, int p) {
    num[u] = low[u] = ind++;
    int childcnt = 0;
    for(int a: adj[u]) {
        if(a == p) continue;
        if(num[a]) {
            low[u] = min(low[u], num[a]);
        } else {
            childcnt++;
            low[u] = min(low[u], dfs(a, u));
            if(low[a] >= num[u] && p != -1) {
                isarti[u]++;
            }
        }

    }
    if(p == -1) isarti[u] = max(0, childcnt-1);
    return low[u];
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int P, C;
    while(cin >> P >> C) {
        if(!P && !C) break;
        adj = vector<vector<int>>(P);
        num = low = isarti = vector<int>(P);
        ind = 1;
        for(int i=0; i<C; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if(!C) {
            cout << P-1 << '\n';
            continue;
        }

        int cnt = 0;
        for(int i=0; i<P; i++) {
            if(!num[i]) {
                cnt++;
                dfs(i, -1);
            }
        }
        int mx = *max_element(isarti.begin(), isarti.end());
        cout << cnt + mx << '\n';
    }
}
