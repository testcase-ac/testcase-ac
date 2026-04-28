#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
int cdist[MAXN][MAXN];
vector<tii> adj[MAXN][MAXN];
int tc, N, M;

void init() {
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    adj[i][j].clear();
    cdist[i][j] = INF;
  }
}

void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];
  init();

  auto oob = [&](int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
  };

  int si, sj, ei, ej;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '#') continue;

    if (board[i][j] == 'O') si = i, sj = j;
    if (board[i][j] == 'X') ei = i, ej = j;

    vector<pii> warp_points;
    for (int k = 0; k < 4; ++k) {
      int ni = i, nj = j, li, lj;
      while (!oob(ni, nj) && board[ni][nj] != '#') {
        li = ni, lj = nj;
        ni += dx[k], nj += dy[k];
      }
      warp_points.emplace_back(li, lj);
    }

    for (auto& [wi1, wj1] : warp_points) for (auto& [wi2, wj2] : warp_points) {
      if (wi1 == wi2 && wj1 == wj2) continue;

      // (i, j) -> (wi1, wj1) -> (wi2, wj2)
      int d1 = abs(wi1 - i) + abs(wj1 - j);
      adj[i][j].emplace_back(wi2, wj2, d1 + 1);
    }

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (oob(ni, nj) || board[ni][nj] == '#') continue;
      adj[i][j].emplace_back(ni, nj, 1);
    }
  }

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.emplace(0, si, sj); cdist[si][sj] = 0;
  while (!pq.empty()) {
    auto [cd, ci, cj] = pq.top(); pq.pop();
    if (cd > cdist[ci][cj]) continue;

    for (auto& [ni, nj, nd] : adj[ci][cj]) {
      if (cd + nd < cdist[ni][nj]) {
        cdist[ni][nj] = cd + nd;
        pq.emplace(cd + nd, ni, nj);
      }
    }
  }

  int ans = cdist[ei][ej];
  if (ans == INF) cout << "THE CAKE IS A LIE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
