#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
int N, M, deg[MAXN];
vector<int> adj[MAXN];

void init() {
  for (int i = 0; i < N; ++i) adj[i].clear();
  fill(deg, deg + N, 0);
}

void solve() {
  init();
  while (M--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v); adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  for (int i = 0; i < N; ++i) {
    if (deg[i] >= 4) return cout << "YES\n", void();
  }

  vector<int> vis(N);
  for (int i = 0; i < N; ++i) {
    if (vis[i]) continue;

    queue<int> q; vector<int> C;
    q.push(i); vis[i] = 1;
    while (!q.empty()) {
      int t = q.front(); q.pop();
      if (deg[t] == 3) C.push_back(t);
      for (int j : adj[t]) {
        if (!vis[j]) vis[j] = 1, q.push(j);
      }
    }

    for (int c1 : C) for (int c2 : C) {
      if (c1 == c2) continue;
      int cnt = 0, f = 0;
      for (int v1 : adj[c1]) for (int v2 : adj[c2]) {
        cnt += (v1 == v2);
        f |= (v1 == c2 || v2 == c1);
      }
      if (cnt <= 1 - f) {
        // cout << "c1 = " << c1 + 1 << ", c2 = " << c2 + 1 << ", cnt = " << cnt << '\n';
        return cout << "YES\n", void();
      }
    }
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  while (cin >> N >> M) solve();
}
