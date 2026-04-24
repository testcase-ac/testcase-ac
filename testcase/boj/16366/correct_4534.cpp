#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1000;
bool human[MX], military[MX];
vector<int> adj[MX][21];
bool seen[MX][MX];
void dfs(int a, int b) {
    if(seen[a][b]) return;
    seen[a][b] = 1;
    if(military[a] && military[b]) {
        cout << "YES" << endl;
        exit(0);
    }
    for(int c=1; c<=20; c++) {
        for(int u: adj[a][c]) {
            for(int v: adj[b][c]) {
                dfs(u, v);
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, W, C, H, M;
    cin >> N >> W >> C >> H >> M;
    for(int i=0; i<H; i++) {
        int t;
        cin >> t;
        human[t] = 1;
    }
    for(int i=0; i<M; i++) {
        int t;
        cin >> t;
        military[t] = 1;
    }
    for(int i=0; i<W; i++) {
        int u, c, v;
        cin >> u >> c >> v;
        adj[u][c].push_back(v);
    }
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            if(human[i] == human[j]) continue;
            dfs(i, j);
        }
    }
    cout << "NO" << endl;
}
