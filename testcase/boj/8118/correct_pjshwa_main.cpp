#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2500;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], ban[MAXN];
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
  int N, x; cin >> N;
  for (int i = 0; i < 3; ++i) cin >> x, ban[x - 1] = 1;

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int u = i * N + j;
    if ((i + j) % 2 || ban[u]) continue;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
      int v = ni * N + nj;
      if (!ban[v]) adj[u].push_back(v);
    }
  }

  int match = 0, T = (N * N - 3) / 2;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int u = i * N + j;
    if ((i + j) % 2 || ban[u] || ma[u] != -1) continue;
    fill(vis, vis + N * N, false);
    if (dfs(u)) ++match;
  }
  if (match != T) return cout << "NIE\n", void();

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int u = i * N + j;
    if ((i + j) % 2 || ban[u]) continue;
    cout << u + 1 << ' ' << ma[u] + 1 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
