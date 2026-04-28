#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 8, MAXT = 8;
const int dx[9] = {0, 0, 1, -1, 1, -1, 1, -1, 0};
const int dy[9] = {1, -1, 0, 0, 1, -1, -1, 1, 0};
char board[MAXN + 1][MAXN + 1];
bool vis[MAXN + 1][MAXN + 1][MAXT + 1];

void solve() {
  int N = 8, M = 8;
  for (int i = 0; i < N; ++i) cin >> board[i];

  // i, j, t
  queue<tuple<int, int, int>> Q;
  Q.emplace(N - 1, 0, 0); vis[N - 1][0][0] = true;

  while (!Q.empty()) {
    auto [i, j, t] = Q.front(); Q.pop();
    int nt = min(t + 1, MAXT);

    // should not have wall at (ni, nj) at both time t and t + 1
    for (int k = 0; k < 9; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (ni - t >= 0 && board[ni - t][nj] == '#') continue;
      if (ni == 0 && nj == M - 1) return cout << "1\n", void();

      if (ni - nt >= 0 && board[ni - nt][nj] == '#') continue;
      if (!vis[ni][nj][nt]) {
        vis[ni][nj][nt] = true;
        Q.emplace(ni, nj, nt);
      }
    }
  }

  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
