#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<int> adj[MAX + 1];
int cdist[MAX + 1];

void bfs() {
  fill(cdist, cdist + MAX + 1, INF);
  queue<int> q;
  q.push(1);
  cdist[1] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();

    for (int v : adj[u]) {
      if (cdist[v] == INF) {
        cdist[v] = cdist[u] + 1;
        q.push(v);
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    
    bfs();
    for (int i = 1; i <= n; i++) {
      if (cdist[i] == INF) cout << -1 << ' ';
      else cout << cdist[i] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
