#include <bits/stdc++.h>
using namespace std;
#define int long long
struct range {
    int l, r;
    void merge(range rng) {
        l = max(l, rng.l);
        r = min(r, rng.r);
    }
    bool include(int t) {
        return l <= t && t <= r;
    }
};
range numbers[201];
range positions[201];
struct biparite {
    int n, m, s;
    vector<int> match, seen;
    vector<vector<int>> adj;
    biparite(int _n, int _m) {
        n = _n, m = _m;
        match.resize(m, -1);
        seen.resize(n, -1);
        adj.resize(n);
    }
    void addedge(int u, int v) {
        adj[u].push_back(v);
    }
    bool dfs(int i) {
        if(seen[i] == s)
            return 0;
        seen[i] = s;
        for(int a: adj[i]) {
            if(match[a] == -1 || dfs(match[a])) {
                match[a] = i;
                return 1;
            }
        }
        return 0;
    }
    int solve() {
        int ans = 0;
        for(int i = 0; i < n; i++) {
            s = i;
            if(dfs(i))
                ans++;
        }
        return ans;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        numbers[i] = positions[i] = {1, n};
    }
    for(int i = 0; i < m; i++) {
        int t, x, y, v;
        cin >> t >> x >> y >> v;
        numbers[v].merge({x, y});
        for(int j = x; j <= y; j++) {
            if(t == 1) {
                positions[j].merge({1, v});
            } else {
                positions[j].merge({v, n});
            }
        }
    }
    biparite bip(n, n);
    for(int p = 1; p <= n; p++) {
        for(int num = 1; num <= n; num++) {
            if(numbers[num].include(p) && positions[p].include(num)) {
                bip.addedge(num - 1, p - 1);
            }
        }
    }
    int res = bip.solve();
    if(res != n)
        return !(cout << -1);
    for(int i = 0; i < n; i++) {
        cout << bip.match[i] + 1 << " ";
    }
}
