#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
int vis[MAX + 1], color[MAX + 1];

bool is_cyclic(int v) {
  if (vis[v] == -1) return true;
  if (vis[v] == 1) return false;

  vis[v] = -1;
  for (auto [u, _] : graph[v]) {
    if (is_cyclic(u)) return true;
  }
  vis[v] = 1;
  return false;
}

bool is_cyclic(int v, int o) {
  if (vis[v] == -1) return true;
  if (vis[v] == 1) return false;

  vis[v] = -1;
  for (auto [u, i] : graph[v]) {
    if (color[i] == o) continue;
    if (is_cyclic(u, o)) return true;
  }
  vis[v] = 1;
  return false;
}

void mark(int v, int c) {
  vis[v] = -1;
  for (auto [u, i] : graph[v]) {
    if (vis[u] == -1) color[i] = 3 - c;
    else {
      color[i] = c;
      if (!vis[u]) mark(u, c);
    }
  }
  vis[v] = 1;
}

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= M; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back({v, i});
  }

  bool cyclic = false;
  for (int i = 1; i <= N; i++) {
    if (vis[i]) continue;
    if (is_cyclic(i)) {
      cyclic = true;
      break;
    }
  }

  if (!cyclic) {
    cout << "1\n" << M << ' ';
    for (int i = 1; i <= M; i++) cout << i << ' ';
    cout << '\n';
    return;
  }

  cout << "2\n";
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= N; i++) {
    if (vis[i]) continue;
    mark(i, 1);
  }

  // memset(vis, 0, sizeof vis);
  // for (int i = 1; i <= N; i++) {
  //   assert(!is_cyclic(i, 1));
  // }
  // memset(vis, 0, sizeof vis);
  // for (int i = 1; i <= N; i++) {
  //   assert(!is_cyclic(i, 2));
  // }

  vector<int> ov, ev;
  for (int i = 1; i <= M; i++) {
    if (color[i] == 1) ov.push_back(i);
    if (color[i] == 2) ev.push_back(i);
  }

  cout << ov.size() << ' ';
  for (int i : ov) cout << i << ' ';
  cout << '\n';
  cout << ev.size() << ' ';
  for (int i : ev) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
