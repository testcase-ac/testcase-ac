#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+1;
// Strongly connected components implementation adapted for this solution.
// Reference: https://cp-algorithms.com/graph/strongly-connected-components.html
vector<bool> visited; // keeps track of which vertices are already visited

void dfs(int v, vector<vector<int>> const& adj, vector<int> &output) {
    visited[v] = true;
    for (auto u : adj[v])
        if (!visited[u])
            dfs(u, adj, output);
    output.push_back(v);
}
void strongy_connected_components(vector<vector<int>> const& adj,
                                  vector<vector<int>> &components,
                                  vector<vector<int>> &adj_cond) {
    int n = adj.size();
    components.clear(), adj_cond.clear();

    vector<int> order;

    visited.assign(n, false);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    vector<vector<int>> adj_rev(n);
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            adj_rev[u].push_back(v);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0);

    for (auto v : order)
        if (!visited[v]) {
            std::vector<int> component;
            dfs(v, adj_rev, component);
            sort(component.begin(), component.end());
            components.push_back(component);
            int root = component.front();
            for (auto u : component)
                roots[u] = root;
        }

    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    while(M--) {
        int u, v;
        cin >> u >> v;
        adj[v-1].push_back(u-1);
    }
    vector<vector<int>> components, adj_cond;
    strongy_connected_components(adj, components, adj_cond);
    int ans = 0;
    for(vector<int> &v: components) {
        int root = v.front();
        if(adj_cond[root].empty()) {
            ans++;
        }
    }
    cout << ans;
}
