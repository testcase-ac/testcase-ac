#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int G[MAXN + 1][MAXN + 1], N;
int Amin[MAXN + 1], Amax[MAXN + 1];
int ma[MAXN + 1], mb[MAXN + 1];
bool vis[MAXN + 1];

bool dfs(int a) {
  vis[a] = true;
  for (int b = 1; b <= N; ++b) {
    if (G[a][b] == 0) continue;
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int M; cin >> N >> M;
  fill(Amin, Amin + N + 1, 1);
  fill(Amax, Amax + N + 1, N);

  // i-th slot can have j as value
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) G[i][j] = 1;

  while (M--) {
    int op, x, y, v; cin >> op >> x >> y >> v;

    // [x, y] must contain v, so other slots cannot have v
    for (int i = 1; i < x; ++i) G[i][v] = 0;
    for (int i = y + 1; i <= N; ++i) G[i][v] = 0;

    for (int i = x; i <= y; ++i) {
      if (op == 1) Amax[i] = min(Amax[i], v);
      if (op == 2) Amin[i] = max(Amin[i], v);
    }
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j < Amin[i]; ++j) G[i][j] = 0;
    for (int j = Amax[i] + 1; j <= N; ++j) G[i][j] = 0;
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N + 1, false);
    if (dfs(i)) ++match;
  }
  if (match < N) return cout << "-1\n", void();

  for (int i = 1; i <= N; ++i) {
    cout << ma[i] << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
