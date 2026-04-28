#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
vector<int> adj[MAXN], adj_r[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }
  if (match == N) return cout << "-1\n", void();

  int r;
  for (r = 0; r < N; ++r) {
    if (ma[r] == -1) break;
  }
  for (int i = 0; i < N; ++i) {
    if (ma[i] == -1) continue;
    adj_r[ma[i]].push_back(i);
  }

  queue<int> q;
  vector<bool> vis(N, false), vis_r(N, false);
  q.push(r); vis[r] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (vis_r[v]) continue;
      vis_r[v] = true;
      for (int w : adj_r[v]) {
        if (vis[w]) continue;
        vis[w] = true; q.push(w);
      }
    }
  }

  cout << accumulate(vis.begin(), vis.end(), 0) << '\n';
  for (int i = 0; i < N; ++i) {
    if (vis[i]) cout << i + 1 << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
