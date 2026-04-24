#include <iostream>
#include <vector>
#include <functional>

using namespace std;
int solve() {
    int N, M;
    cin >> N >> M;
    if(N==0 && M==0) return -1;
    vector<vector<int>> adj(N+1);
    for(int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<char> seen(N+1, 0);
    function<bool(int, int)> dfs = [&](int u, int p) {
        bool backedge = false;
        seen[u] = 1;
        for(int a: adj[u]) {
            if(a==p) continue;
            if(seen[a]) {
                backedge = true;
                continue;
            }
            if(dfs(a, u)) {
                backedge = true;
            }
        }
        return backedge;
    };
    int cnt = 0;
    for(int i=1; i<=N; i++) {
        if(seen[i]) continue;
        if(!dfs(i, -1)) {
            cnt++;
        }
    }
    return cnt;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    for(int c=1; ; c++) {
        int cnt = solve();
        if(cnt==-1) break;
        if(cnt==0) {
            printf("Case %d: No trees.\n", c);
        } else if(cnt==1) {
            printf("Case %d: There is one tree.\n", c);
        } else {
            printf("Case %d: A forest of %d trees.\n", c, cnt);
        }
    }
}
