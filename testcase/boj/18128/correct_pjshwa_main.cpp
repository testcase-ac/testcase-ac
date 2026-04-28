#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
const int dx8[8] = {0, 0, 1, -1, 1, 1, -1, -1}, dy8[8] = {1, -1, 0, 0, 1, -1, 1, -1};
char board[MAXN + 1][MAXN + 1];
int D[MAXN][MAXN], V[MAXN][MAXN];

void solve() {
  int N, W; cin >> N >> W;

  memset(D, 0x3f, sizeof(D));
  queue<pii> Q;
  while (W--) {
    int r, c; cin >> r >> c; --r, --c;
    D[r][c] = 0; Q.emplace(r, c);
  }
  for (int i = 0; i < N; ++i) cin >> board[i];

  while (!Q.empty()) {
    auto [r, c] = Q.front(); Q.pop();
    for (int k = 0; k < 4; ++k) {
      int nr = r + dx[k], nc = c + dy[k];
      if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
      if (D[nr][nc] > D[r][c] + 1) {
        D[nr][nc] = D[r][c] + 1;
        Q.emplace(nr, nc);
      }
    }
  }
  D[N - 1][N - 1] = 0;

  int l = 0, r = 2 * N + 1;
  while (l < r) {
    int m = (l + r) / 2;

    memset(V, 0, sizeof(V));
    Q.emplace(0, 0); V[0][0] = 1;
    while (!Q.empty()) {
      auto [r, c] = Q.front(); Q.pop();
      for (int k = 0; k < 8; ++k) {
        int nr = r + dx8[k], nc = c + dy8[k];
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
        if (board[nr][nc] == '0' || D[nr][nc] > m || V[nr][nc]) continue;
        Q.emplace(nr, nc); V[nr][nc] = 1;
      }
    }

    if (V[N - 1][N - 1]) r = m;
    else l = m + 1;
  }

  if (l == 2 * N + 1) cout << "-1\n";
  else cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
