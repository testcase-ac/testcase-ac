#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN];
bool vis[MAXN * MAXN];
int B[MAXN][MAXN];

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
  int N, M, x; cin >> M >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> B[i][j];
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> x, B[i][j] -= x;

  int sum = 0, all = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) sum += B[i][j], all += abs(B[i][j]);
  if (sum != 0) return cout << "-1\n", void();

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (B[i][j] == 1 && B[ni][nj] == -1) {
        adj[i * M + j].push_back(ni * M + nj);
      }
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N * M; i++) {
    if (ma[i] != -1) continue;
    memset(vis, 0, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << all - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
