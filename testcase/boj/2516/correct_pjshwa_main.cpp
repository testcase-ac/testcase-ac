#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 1];
int S[MAXN + 1], deg[MAXN + 1];

void solve() {
  int n; cin >> n;

  fill(S + 1, S + n + 1, 1); S[1] = 2;
  for (int u = 1; u <= n; ++u) {
    int c; cin >> c;
    while (c--) {
      int v; cin >> v;
      adj[u].push_back(v);
      ++deg[v];
    }
  }

  bool f = true;
  while (f) {
    f = false;
    for (int u = 1; u <= n; ++u) {
      int cnt = 0;
      for (int v : adj[u]) {
        if (S[u] == S[v]) ++cnt;
      }
      if (cnt > 1) {
        S[u] = 3 - S[u];
        f = true;
      }
    }
  }

  vector<int> g1, g2;
  for (int u = 1; u <= n; ++u) {
    if (S[u] == 1) g1.push_back(u);
    else g2.push_back(u);
  }

  cout << g1.size() << ' '; for (int u : g1) cout << u << ' '; cout << '\n';
  cout << g2.size() << ' '; for (int u : g2) cout << u << ' '; cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
