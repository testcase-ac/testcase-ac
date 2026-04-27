#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<pair<int, int>> bin(n);
    for (auto &[a, b] : bin) cin >> a >> b;

    vector<int> out_degree(n + 1);
    vector<vector<int>> graph(n + 1);
    for (auto [a, b] : bin) {
        graph[a].push_back(b);
        graph[b].push_back(a);

        out_degree[b]++;
    }

    vector<int> vis(n + 1), tmp;

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        tmp.push_back(u);
        for (int v : graph[u]) {
            if (vis[v]) continue;
            dfs(v);
        }
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            tmp.clear();
            dfs(i);

            if (tmp.size() == 1) continue; // self loop

            int cnt = 0;
            for (int u : tmp) cnt += out_degree[u] >= 2;

            if (cnt >= 2) return cout << -1, 0;

            ans += tmp.size() + 1;
        }
    }

    cout << ans << '\n';
}
