#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<vector<bool>> grid(N+1, vector<bool>(N+1, 1));
    vector<vector<int>> adj(N+1);
    vector<int> color(N+1, -1);
    for(int i=0; i<M; i++) {
        int u, v;
        cin >> u >> v;
        grid[u][v] = grid[v][u] = 0;
    }
    for(int i=1; i<=N; i++) {
        for(int j=i+1; j<=N; j++) {
            if(grid[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    int zero = 0, one = 0, fail = 0;
    function<void(int)> dfs = [&](int i) {
        for(int j: adj[i]) {
            if(color[j] == -1) {
                color[j] = color[i]^1;
                if(color[j] == 0) zero++;
                else one++;
                dfs(j);
            } else if(color[j] == color[i]) {
                fail = 1;
            }
        }
    };
    vector<pair<int, int>> rec;
    int recsum = 0;
    int remain = N;
    for(int i=1; i<=N; i++) {
        if(color[i] == -1 && adj[i].size()) {
            zero = 1, one = 0;
            color[i] = 0;
            dfs(i);
            if(fail) {
                return !(cout << -1);
            }
            remain -= zero + one;
            recsum += zero+one;
            if(zero > one) swap(zero, one);
            rec.push_back({zero, one});
        }
    }
    vector<vector<bool>> dp(rec.size()+1, vector<bool>(N+1, 0));
    dp[0][0] = 1;
    for(int i=0; i<rec.size(); i++) {
        for(int j=0; j<=N; j++) {
            if(dp[i][j]) {
                dp[i+1][j+rec[i].first] = dp[i+1][j+rec[i].second] = 1;
            }
        }
    }
    int ans = INT_MAX;
    for(int i=0; i<=N; i++) {
        if(!dp[rec.size()][i]) {
            continue;
        }
        int a = i;
        int b = recsum - a;
        if(a > b) swap(a, b);
        if(b-a > remain) {
            ans = min(ans, b-a-remain);
        } else {
            ans = N % 2;
        }
    }
    cout << ans;
}
