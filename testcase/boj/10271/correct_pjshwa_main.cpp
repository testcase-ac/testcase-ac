#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e4, INF = 0x3f3f3f3f;
vector<int> adj[MAXN + 1], radj[MAXN + 1];
int N, indegree[MAXN + 1];

void solve() {
  cin >> N;
  for (int i = 1; i < N; ++i) {
    int k; cin >> k;
    while (k--) {
      int u; cin >> u;
      adj[i].push_back(u); radj[u].push_back(i);
    }
  }

  queue<int> q;
  vector<bool> vis1(N + 1), vis2(N + 1);
  q.push(1); vis1[1] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (!vis1[v]) vis1[v] = true, q.push(v);
    }
  }
  q.push(N); vis2[N] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : radj[u]) {
      if (!vis2[v]) vis2[v] = true, q.push(v);
    }
  }
  
  bool ok = vis1[N];
  for (int i = 1; i <= N; ++i) {
    if (vis1[i] && !vis2[i]) ok = 0;
  }
  if (ok) cout << "PARDON ";
  else cout << "PRISON ";

  for (int i = 1; i <= N; ++i) {
    if (!vis1[i]) continue;
    for (int v : adj[i]) indegree[v] += vis1[v];
  }
  if (indegree[1] == 0) q.push(1);
  int tot = accumulate(vis1.begin(), vis1.end(), 0);
  for (int i = 1; i <= tot; ++i) {
    if (q.empty()) return cout << "UNLIMITED\n", void();
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (!--indegree[v]) q.push(v);
    }
  }
  cout << "LIMITED\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
