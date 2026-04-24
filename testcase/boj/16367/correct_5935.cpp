#include <bits/stdc++.h>
using namespace std;
#define int long long
struct SAT {
    vector<vector<int>> adj;
    vector<int> val, num, low, stk, scc, visiting;
    int nxt, n, cnt;
    int f(int i) {
        if(i < 0) i = -i+n;
        return i;
    }
    int neg(int i) {
        if(i >= n)
            return i-n;
        return i + n;
    }
    SAT(int _n, vector<pair<int, int>>& edges) { // 입력 n: 변수의 개수
        n = _n+1;
        adj.resize(2*n+1);
        val.resize(2*n+1);
        num.resize(2*n+1);
        low.resize(2*n+1);
        scc.resize(2*n+1);
        visiting.resize(2*n+1);
        nxt = 1;
        for(auto [a, b]: edges) {
            a = f(a), b = f(b);
            adj[neg(a)].push_back(b);
            adj[neg(b)].push_back(a);
        }
        compute();
    }
    void compute() {
        for(int i=1; i<=n; i++) {
            if(!num[i])
                dfs(i);
        }
        for(int i=n+1; i<=n+n; i++) {
            if(!num[i])
                dfs(i);
        }
    }
    void dfs(int i) {
        num[i] = low[i] = nxt++;
        visiting[i] = 1;
        stk.push_back(i);
        for(int a: adj[i]) {
            if(!num[a]) {
                dfs(a);
            }
            if(visiting[a]) {
                low[i] = min(low[i], low[a]);
            }
        }
        if(num[i] == low[i]) {
            int c = cnt++;
            while(1) {
                int t = stk.back();
                stk.pop_back();
                scc[t] = c;
                visiting[t] = 0;
                if(t == i) break;
            }
        }
    }
    bool ok() {
        for(int i=1; i<=n; i++) {
            if(scc[i] == scc[neg(i)])
                return 0;
        }
        return 1;
    }
    vector<int> result() {
        vector<int> ans(n+1);
        for(int i=1; i<=n; i++) {
            ans[i] = (scc[i] < scc[neg(i)]);
        }
        return ans;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int K, N;
    cin >> K >> N;
    vector<pair<int, int>> edges;
    while(N--) {
        vector<pair<int, int>> v(3);
        for(int i=0; i<3; i++) {
            int t;
            char c;
            cin >> t >> c;
            v[i].first = t;
            v[i].second = (c == 'R') ? 1 : -1;
        }
        for(int i=0; i<3; i++) {
            for(int j=i+1; j<3; j++) {
                edges.push_back({v[i].first * v[i].second, v[j].first * v[j].second});
            }
        }
    }
    SAT sat(K+1, edges);
    if(!sat.ok()) {
        return !(cout << -1);
    }
    vector<int> res = sat.result();
    for(int i=1; i<=K; i++) {
        cout << (res[i] == 1 ? "R" : "B");
    }
}
