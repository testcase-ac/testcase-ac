#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
vector<int> adj[MAX + 1];
int deg[MAX + 1];
int adist[MAX + 1], bdist[MAX + 1], cdist[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }

  int a, b, c; cin >> a >> b >> c;
  memset(adist, 0x3f, sizeof(adist));
  memset(bdist, 0x3f, sizeof(bdist));
  memset(cdist, 0x3f, sizeof(cdist));

  queue<int> q;
  q.push(a); adist[a] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (adist[v] > adist[u] + 1) adist[v] = adist[u] + 1, q.push(v);
    }
  }

  q.push(b); bdist[b] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (bdist[v] > bdist[u] + 1) bdist[v] = bdist[u] + 1, q.push(v);
    }
  }

  q.push(c); cdist[c] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (cdist[v] > cdist[u] + 1) cdist[v] = cdist[u] + 1, q.push(v);
    }
  }

  for (int i = 1; i <= N; i++) {
    if (deg[i] != 1) continue;
    if (adist[i] < bdist[i] && adist[i] < cdist[i]) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
