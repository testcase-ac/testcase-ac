#include <iostream>
#include <array>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

struct Triple { int a, b, c; Triple(int a, int b, int c) : a(a), b(b), c(c) {} };

vector<Triple> res;
array<vector<int>, 100'000> adj;
bitset<100'000> vis, on_stack;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](const auto& self, int u, int p) -> bool {
        int last = -1;
        vis.set(u);
        on_stack.set(u);
        for (int v : adj[u]) {
            if (v == p || (vis.test(v) && !on_stack.test(v))) { continue; }
            if (on_stack.test(v) || self(self, v, u)) {
                if (last == -1) { last = v; }
                else {
                    res.emplace_back(last, u, v);
                    last = -1;
                }
            }
        }
        
        on_stack.reset(u);
        if (last == -1) { return true; }
        if (u != p) { res.emplace_back(last, u, p); }
        return false;
    };
    for (int i = 0; i < n; i++) {
        if (vis.test(i)) { continue; }
        dfs(dfs, i, i);
    }

    cout << res.size() << "\n";
    for (const auto& [a, b, c] : res) {
        cout << a+1 << " " << b+1 << " " << c+1 << "\n";
    }

    return 0;
}
