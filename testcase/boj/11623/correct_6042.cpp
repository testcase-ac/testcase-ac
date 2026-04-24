#include <bits/stdc++.h>
using namespace std;

int n;
int adj[200001];
int deg[200001];
bool used[200001];
vector<int> s;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int tmp; cin >> tmp;
        adj[i] = tmp;
        ++deg[tmp];
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        int tmp; cin >> tmp;
        adj[i] = tmp;
        ++deg[tmp];
    }
    queue<int> q;
    for (int i = 1; i <= 2 * n; ++i) {
        if (deg[i] == 0) {
            q.push(i);
            used[i] = true;
        }
    }
    while (!q.empty()) {
        int here = q.front(); q.pop();
        // cout << here << '\n';
        s.push_back(here);
        // used[here] = true;
        if (used[adj[here]]) continue;
        used[adj[here]] = true;

        int tmp = adj[adj[here]];
        --deg[tmp];
        if (deg[tmp] == 0 && !used[tmp]) {
            q.push(tmp);
            used[tmp] = true;
        }
    }
    for (int i = 1; i <= n; ++i) if (!used[i]) s.push_back(i);
    for (auto i: s) cout << i << ' ';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
