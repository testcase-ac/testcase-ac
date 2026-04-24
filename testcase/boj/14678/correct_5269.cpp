#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MX = 1000002;
vector<int> adj[MX];
int height[MX], cnt[2], ans;
void dfs(int i) {
    if(adj[i].size() == 1)
        cnt[height[i]&1]++;
    for(int a: adj[i]) {
        if(height[a] == -1) {
            height[a] = height[i]+1;
            dfs(a);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin >> n;
    if(n == 1)
        return !(cout << 1);
    for(int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(height, -1, sizeof height);
    height[1] = 1;
    dfs(1);
    for(int i=1; i<=n; i++) {
        if(adj[i].size() == 1) {
            cnt[height[i]&1]--;
        }
        ans = max(ans, (height[i]&1) ? cnt[1] : cnt[0]);
        if(adj[i].size() == 1) {
            cnt[height[i]&1]++;
        }
    }
    cout << ans;
}
