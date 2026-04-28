#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<tii> adj[MAX + 1];
int ginv[MAX + 1], vis[MAX + 1], is_cycle[MAX + 1];
int S[MAX + 1];
map<int, int> E[MAX + 1];
int n;

void mark_cycle(int v, int p) {
  vis[v] = 1;
  for (auto& [u, h, i] : adj[v]) {
    if (!vis[u]) ginv[u] = v, mark_cycle(u, v);
    else if (p != u && !is_cycle[u]) {
      // Cycle is detected
      for (int x = v; x != u; x = ginv[x]) is_cycle[x] = 1;
      is_cycle[u] = 1;
    }
  }
}

void mark_ans(int v, int p) {
  vis[v] = 1;
  for (auto& [u, h, i] : adj[v]) {
    if (u == p) E[u][h]++;
    else {
      S[i] = u;
      if (!vis[u]) mark_ans(u, v);
    }
  }
}

void print_ans() {
  for (int i = 1; i <= n; i++) cout << S[i] << '\n';
  exit(0);
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int u, v, h; cin >> u >> v >> h;
    adj[u].emplace_back(v, h, i);
    adj[v].emplace_back(u, h, i);
  }
  mark_cycle(1, -1);

  int t, v1 = -1, v2;
  for (int i = 1; i <= n; i++) if (is_cycle[i]) t = i;
  for (auto& [v, _, i] : adj[t]) {
    if (!is_cycle[v]) continue;
    if (v1 == -1) v1 = v;
    else v2 = v;
  }

  {
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) E[i].clear();
    mark_ans(t, v1);

    int f = 1;
    for (int i = 1; i <= n; i++) for (auto& [h, c] : E[i]) f &= c == 1;
    if (f) print_ans();
  }
  {
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) E[i].clear();
    mark_ans(t, v2);

    int f = 1;
    for (int i = 1; i <= n; i++) for (auto& [h, c] : E[i]) f &= c == 1;
    if (f) print_ans();
  }

  cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
