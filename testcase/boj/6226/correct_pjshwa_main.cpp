#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 30, MAXT = 200, INF = 0x3f3f3f3f;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int A[MAXN][MAXN], cdist[MAXN][MAXN][MAXT]; ll dp[MAXN][MAXN][MAXT];
int si, sj, ei, ej, at;

ll dfs(int i, int j, int t) {
  if (i == ei && j == ej) return dp[i][j][t] = t == at;
  if (dp[i][j][t] != -1) return dp[i][j][t];

  ll ret = 0;
  for (int k = 0; k < 8; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    int nt = t + (A[ni][nj] == 1 ? 0 : 1);
    if (ni < 0 || ni >= MAXN || nj < 0 || nj >= MAXN || nt >= MAXT) continue;
    if (cdist[ni][nj][nt] == cdist[i][j][t] + 1) ret += dfs(ni, nj, nt);
  }
  return dp[i][j][t] = ret;
}

void solve() {
  int N, M; cin >> N >> M;

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    cin >> A[i][j];
    if (A[i][j] == 3) si = i, sj = j, A[i][j] = 1;
    if (A[i][j] == 4) ei = i, ej = j, A[i][j] = 1;
  }

  memset(cdist, 0x3f, sizeof(cdist));
  queue<tuple<int, int, int>> Q;
  Q.emplace(si, sj, 0); cdist[si][sj][0] = 0;

  while (!Q.empty()) {
    auto [i, j, t] = Q.front(); Q.pop();

    for (int k = 0; k < 8; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M || A[ni][nj] == 2) continue;

      int nt = t + (A[ni][nj] == 1 ? 0 : 1);
      if (nt < MAXT && cdist[ni][nj][nt] > cdist[i][j][t] + 1) {
        cdist[ni][nj][nt] = cdist[i][j][t] + 1;
        Q.emplace(ni, nj, nt);
      }
    }
  }

  for (at = 0; at < MAXT; ++at) {
    if (cdist[ei][ej][at] != INF) break;
  }
  if (at == MAXT) return cout << "-1\n", void();

  cout << at << '\n' << cdist[ei][ej][at] << '\n';

  memset(dp, -1, sizeof(dp));
  cout << dfs(si, sj, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
