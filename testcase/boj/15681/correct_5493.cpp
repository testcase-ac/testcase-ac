#include <iostream>
#include <vector>
#include <functional>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<vector<int>> adj(N+1);
    vector<int> dp(N+1, 0);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    function<void(int, int)> dfs = [&](int a, int p) {
        dp[a] = 1;
        for (int b : adj[a]) {
            if (b == p) continue;
            dfs(b, a);
            dp[a] += dp[b];
        }
    };
    dfs(R, -1);
    for (int i = 0; i < Q; i++) {
        int a;
        cin >> a;
        cout << dp[a] << '\n';
    }
    return 0;
}
