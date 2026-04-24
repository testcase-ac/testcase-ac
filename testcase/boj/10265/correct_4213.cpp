#include <bits/stdc++.h>
using namespace std;
const int MX = 1001;
vector<int> adj[MX], adjt[MX];
stack<int> st;
bool seen[MX];
vector<vector<int>> cc;
void dfs1(int i) {
    seen[i] = 1;
    for(int a: adj[i]) {
        if(!seen[a])
            dfs1(a);
    }
    st.push(i);
}
void dfs2(int i) {
    seen[i] = 1;
    cc.back().push_back(i);
    for(int a: adjt[i]) {
        if(!seen[a])
            dfs2(a);
    }
}
void scc(int v) {
    for(int i = 1; i <= v; i++)
        if(!seen[i])
            dfs1(i);
    memset(seen, 0, sizeof seen);
    while(!st.empty()) {
        int i = st.top();
        st.pop();
        if(!seen[i]) {
            cc.emplace_back();
            dfs2(i);
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        int t;
        cin >> t;
        if(i != t) {
            adj[t].push_back(i);
            adjt[i].push_back(t);
        }
    }
    scc(N);
    memset(seen, 0, sizeof seen);
    vector<pair<int, int>> config;
    for(auto &v: cc) {
        bool root = 1;
        for(int i: v) {
            if(seen[i]) {
                root = 0;
            }
        }
        for(int i: v) {
            for(int a: adj[i]) {
                seen[a] = 1;
            }
        }
        if(root) {
            config.push_back({v.size(), v.size()});
        } else {
            config.back().second += v.size();
        }
    }
    vector<vector<bool>> dp(config.size() + 1, vector<bool>(K + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= config.size(); i++) {
        for(int j = 0; j <= K; j++) {
            if(dp[i - 1][j]) {
                dp[i][j] = 1;
                int st = j + config[i - 1].first;
                int ed = min(j + config[i - 1].second + 1, K + 1);
                if(st <= ed)
                    fill(dp[i].begin() + st, dp[i].begin() + ed, 1);
            }
        }
    }
    for(int i = K; i >= 0; i--) {
        if(dp[config.size()][i]) {
            cout << i << '\n';
            break;
        }
    }
}
