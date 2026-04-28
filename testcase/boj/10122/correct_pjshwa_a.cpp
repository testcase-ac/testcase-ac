#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<vector<int>> nodes(n);
    vector<int> dep(n);

    vector<int> stk;
    stk.reserve(n - 1);

    auto dfs = [&](int s) {
        dep[s] = 0;
        stk.emplace_back(s);
        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            nodes[dep[u]].emplace_back(s);
            for (const auto& v : adj[u])
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    stk.emplace_back(v);
                }
        }
    };

    int64_t ans = 0;
    for (int root = 0; root < n; ++root) {
        fill(dep.begin(), dep.end(), -1);
        dep[root] = INT_MIN;

        for (auto& vt : nodes)
            vt.clear();

        for (const auto& sub_root : adj[root])
            dfs(sub_root);

        for (auto& vt : nodes) {
            sort(vt.begin(), vt.end());
            int64_t dp1 = 0, dp2 = 0;
            for (int i = 0, j; i != int(vt.size()); i = j) {
                for (j = i + 1; j != int(vt.size()) && vt[i] == vt[j]; ++j)
                    ;
                ans += dp2 * (j - i);
                dp2 += dp1 * (j - i);
                dp1 += (j - i);
            }
        }
    }
    cout << ans;
}
