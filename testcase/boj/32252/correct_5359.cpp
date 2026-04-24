#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
    int v, w;
    bool operator<(const edge &e) const {
        return w > e.w;
    }
};
const int MX = 3e5+1;
int unit[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, s, e;
    cin >> N >> M >> s >> e;
    vector<vector<edge>> adj(N+1);
    for(int i=0; i<M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    queue<int> que;
    que.push(e);
    fill(unit, unit+N+1, LLONG_MAX);
    unit[e] = 0;
    while(que.size()) {
        int s = que.size();
        while(s--) {
            int u = que.front();
            que.pop();
            for(auto [v, _]: adj[u]) {
                if(unit[v] == LLONG_MAX) {
                    unit[v] = unit[u] + 1;
                    que.push(v);
                }
            }
        }
    }
    vector<int> zero_reachable(N+1);
    zero_reachable[s] = 1;
    function<void(int)> dfs = [&](int u) {
        // printf("dfs visit %lld\n", u);
        for(auto [v, w]: adj[u]) {
            if(w == 1) continue;
            if(!zero_reachable[v]) {
                zero_reachable[v] = 1;
                dfs(v);
            }
        }
    };

    dfs(s);
    if(zero_reachable[e] == 1) {
        cout << 0 << '\n';
        return 0;
    }
    vector<int> v;
    int mn_dist = LLONG_MAX;
    for(int i=1; i<=N; i++) {
        if(zero_reachable[i]) {
            if(unit[i] < mn_dist) {
                mn_dist = unit[i];
                v = {i};
            } else if(unit[i] == mn_dist) {
                v.push_back(i);
            }
        }
    }
    // printf("starters are: ");
    // for(int i: v) {
    //     printf("%lld, ", i);
    // }
    // printf("\n");
    string ans;
    while(true) {
        vector<int> nxtv_one, nxtv_zero;
        set<int> one_st, zero_st;
        for(int i: v) {
            for(auto [v, w]: adj[i]) {
                if(unit[v] == unit[i]-1) {
                    if(w == 0) {
                        if(!zero_st.count(v)) {
                            zero_st.insert(v);
                            nxtv_zero.push_back(v);
                        }
                    } else {
                        if(!one_st.count(v)) {
                            one_st.insert(v);
                            nxtv_one.push_back(v);
                        }
                    }
                }
            }
        }
        if(nxtv_zero.size()) {
            // printf("zero ok. nxt are: ");
            // for(int i: nxtv_zero) {
            //     printf("%lld, ", i);
            // }
            // printf("\n");
            ans += '0';
            v = nxtv_zero;
        } else {
            // printf("one ok. nxt are: ");
            // for(int i: nxtv_one) {
            //     printf("%lld, ", i);
            // }
            // printf("\n");
            ans += '1';
            v = nxtv_one;
        }
        if(unit[v[0]] == 0) break;
    }
    cout << ans << '\n';
}
