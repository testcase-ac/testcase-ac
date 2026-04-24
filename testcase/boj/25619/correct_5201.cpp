#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 200001;
struct edge {
    int v, w;
    bool operator<(const edge &o) const {
        return w > o.w;
    }
};
vector<edge> adj[MX];
bool seen[MX];
bool has_neg = 0;
void dfs(int i, int p) {
    if(seen[i])
        return;
    seen[i] = 1;
    for(auto [a, w]: adj[i]) {
        if(a == p) {
            continue;
        }
        if(w < 0) {
            has_neg = 1;
        }
        dfs(a, i);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, T;
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        adj[u].push_back({v, a + b});
        adj[v].push_back({u, a + b});
    }
    cin >> T;
    dfs(1, 0);
    if(has_neg) {
        int cnt = 0;
        for(int i = 2; i <= N; i++) {
            if(seen[i]) {
                cnt++;
            }
        }
        cout << cnt << '\n';
        for(int i = 2; i <= N; i++) {
            if(seen[i]) {
                cout << i << ' ';
            }
        }
        return 0;
    }
    priority_queue<edge> pq;
    vector<int> dist(N + 1, 1e18);
    dist[1] = 0;
    pq.push({1, 0});
    while(pq.size()) {
        auto [i, d] = pq.top();
        pq.pop();
        if(d > dist[i]) {
            continue;
        }
        for(auto [a, w]: adj[i]) {
            if(dist[a] > dist[i] + w) {
                dist[a] = dist[i] + w;
                pq.push({a, dist[a]});
            }
        }
    }
    int cnt = 0;
    for(int i = 2; i <= N; i++) {
        if(dist[i] <= T * 2) {
            cnt++;
        }
    }
    cout << cnt << '\n';
    for(int i = 2; i <= N; i++) {
        if(dist[i] <= T * 2) {
            cout << i << ' ';
        }
    }
}
