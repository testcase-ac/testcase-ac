#include <bits/stdc++.h>
using namespace std;
struct SAT {
    vector<vector<int>> adj;
    vector<int> val, num, low, stk, scc, visiting;
    int nxt, n, cnt;
    int f(int i) {
        if(i < 0) i = -i + n;
        return i;
    }
    int neg(int i) {
        if(i >= n)
            return i - n;
        return i + n;
    }
    SAT(int _n, vector<pair<int, int>>& edges) {  // 입력 n: 변수의 개수
        n = _n + 1;
        adj.resize(2 * n + 1);
        val.resize(2 * n + 1);
        num.resize(2 * n + 1);
        low.resize(2 * n + 1);
        scc.resize(2 * n + 1);
        visiting.resize(2 * n + 1);
        nxt = 1;
        for(auto [a, b]: edges) {
            a = f(a), b = f(b);
            adj[neg(a)].push_back(b);
            adj[neg(b)].push_back(a);
        }
        compute();
    }
    void compute() {
        for(int i = 1; i <= n; i++) {
            if(!num[i])
                dfs(i);
        }
        for(int i = n + 1; i <= n + n; i++) {
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
        for(int i = 1; i <= n; i++) {
            if(scc[i] == scc[neg(i)])
                return 0;
        }
        return 1;
    }
    vector<int> result() {
        vector<int> ans(n + 1);
        for(int i = 1; i <= n; i++) {
            ans[i] = (scc[i] < scc[neg(i)]);
        }
        return ans;
    }
};
int N, teacher[201], like[201][201];
bool solve(int t) {
    vector<pair<int, int>> edges;
    for(int i = 1; i <= N; i++) {
        int fst = i * 2 - 1, snd = i * 2;
        edges.push_back({fst, snd});
        edges.push_back({-fst, -snd});
        for(int ji = t + 1; ji < N; ji++) {
            int j = like[i][ji];
            int fst_j = j * 2 - 1,
                snd_j = j * 2;
            if(teacher[i] == teacher[j]) {
                edges.push_back({-fst, -fst_j});
                edges.push_back({-snd, -snd_j});
            }
            if(teacher[i] == 0) {
                if(teacher[j] == 1) {
                    edges.push_back({-snd, -snd_j});
                }
                if(teacher[j] == 2) {
                    edges.push_back({-fst, -snd_j});
                }
            } else if(teacher[i] == 1) {
                if(teacher[j] == 0) {
                    edges.push_back({-snd, -snd_j});
                }
                if(teacher[j] == 2) {
                    edges.push_back({-fst, -fst_j});
                }
            } else if(teacher[i] == 2) {
                if(teacher[j] == 0) {
                    edges.push_back({-snd, -fst_j});
                }
                if(teacher[j] == 1) {
                    edges.push_back({-fst, -fst_j});
                }
            }
        }
    }
    SAT sat(2 * N, edges);
    return sat.ok();
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> teacher[i];
        for(int j = 1; j < N; j++) {
            cin >> like[i][j];
        }
    }
    int l = 0, r = N;
    while(l < r) {
        int m = (l + r) / 2;
        if(solve(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}
