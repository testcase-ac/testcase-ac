#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5 + 1;
vector<int> adj[MX];
int p[MX], sz[MX];
int f(int i) {
    if(p[i] == i) return i;
    return p[i] = f(p[i]);
}
void join(int a, int b) {
    a = f(a);
    b = f(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
}
bool check_has_edge(int a, int b) {
    if(!binary_search(adj[a].begin(), adj[a].end(), b)) {
        join(a, b);
        return false;
    }
    return true;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> v(N);
    for(int i = 0; i < N; i++) {
        v[i] = i + 1;
        p[i + 1] = i + 1;
        sz[i + 1] = 1;
        sort(adj[i + 1].begin(), adj[i + 1].end());
    }

    int mn = 1;
    for(int i = 2; i <= N; i++) {
        if(adj[i].size() < adj[mn].size())
            mn = i;
    }
    vector<int> init_group, extra_group;
    for(int i = 1; i <= N; i++) {
        if(i == mn) {
            init_group.push_back(i);
            continue;
        }
        if(check_has_edge(i, mn)) {
            extra_group.push_back(i);
        } else {
            init_group.push_back(i);
        }
    }
    for(int t: extra_group) {
        for(int i: init_group) {
            check_has_edge(i, t);
        }
        for(int t2: extra_group) {
            if(t2 == t) continue;
            check_has_edge(t, t2);
        }
    }

    vector<int> ans;
    for(int i = 1; i <= N; i++) {
        if(f(i) == i) {
            ans.push_back(sz[i]);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int t: ans) {
        cout << t << ' ';
    }
}
