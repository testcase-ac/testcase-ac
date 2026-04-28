#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
int Sm[5], Dm[5][5], Em[5];
int cdist[MAXN][MAXN];
int N, M;

// calculate distance from starting point
void f_cdist(int i, int j) {
  memset(cdist, 0x3f, sizeof(cdist));

  queue<pii> q;
  q.emplace(i, j); cdist[i][j] = 0;
  while (!q.empty()) {
    auto [ci, cj] = q.front(); q.pop();
    for (int k = 0; k < 4; ++k) {
      int ni = ci + dx[k], nj = cj + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == '#' || cdist[ni][nj] != INF) continue;
      cdist[ni][nj] = cdist[ci][cj] + 1;
      q.emplace(ni, nj);
    }
  }
}

void solve() {
  cin >> M >> N;

  int si, sj, ei, ej, W = 0;
  vector<pii> Wp;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == 'S') si = i, sj = j;
      if (board[i][j] == 'E') ei = i, ej = j;
      if (board[i][j] == 'X') {
        Wp.emplace_back(i, j);
        ++W;
      }
    }
  }

  f_cdist(si, sj);
  if (W == 0) return cout << cdist[ei][ej] << '\n', void();
  for (int t = 0; t < W; ++t) {
    auto [wi, wj] = Wp[t];
    Sm[t] = cdist[wi][wj];
  }

  for (int t = 0; t < W; ++t) {
    auto [wi_s, wj_s] = Wp[t];
    f_cdist(wi_s, wj_s);

    for (int u = 0; u < W; ++u) {
      auto [wi_e, wj_e] = Wp[u];
      Dm[t][u] = cdist[wi_e][wj_e];
    }
    Em[t] = cdist[ei][ej];
  }

  int p[W], ans = INF;
  iota(p, p + W, 0);

  do {
    if (Sm[p[0]] == INF || Em[p[W - 1]] == INF) continue;

    int cur = Sm[p[0]] + Em[p[W - 1]], ok = 1;
    for (int i = 1; i < W; ++i) {
      if (Dm[p[i - 1]][p[i]] == INF) {
        ok = 0;
        break;
      }
      cur += Dm[p[i - 1]][p[i]];
    }
    if (ok) ans = min(ans, cur);

  } while (next_permutation(p, p + W));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
