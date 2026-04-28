#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MAXL = 20000;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  vector<pii> D[MAXL + 1]; set<int> P;
  for (int di = 1; di < N; ++di) for (int dj = 1; dj < M; ++dj) {
    int td = di * di + dj * dj;

    P.insert(td);
    D[td].push_back({di, dj});
    D[td].push_back({di, -dj});
    D[td].push_back({-di, dj});
    D[td].push_back({-di, -dj});
  }
  for (int di = 1; di < N; ++di) {
    int td = di * di;

    P.insert(td);
    D[td].push_back({di, 0});
    D[td].push_back({-di, 0});
  }
  for (int dj = 1; dj < M; ++dj) {
    int td = dj * dj;

    P.insert(td);
    D[td].push_back({0, dj});
    D[td].push_back({0, -dj});
  }

  vector<pii> Ls;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == 'L') Ls.push_back({i, j});
  }

  int ans = 0;
  for (int d : P) {
    for (auto& [i, j] : Ls) {
      if (board[i][j] != 'L') continue;

      int cnt = 0;
      for (auto [di, dj] : D[d]) {
        int ni = i + di, nj = j + dj;
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        if (board[ni][nj] == 'X') {
          ++cnt;
          board[ni][nj] = '.';
        }
      }

      if (cnt >= 1) {
        if (cnt > 1) ++ans;
        board[i][j] = '.';
      }

    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
