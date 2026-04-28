#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
map<vector<pii>, int> cdist;

void solve() {
  int n, w, h, l; cin >> n >> w >> h >> l;
  for (int i = 0; i < h; ++i) cin >> board[i];

  vector<pii> P(n); pii E;
  for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
    char c = board[i][j];
    if (isdigit(c)) P[c - '1'] = {i, j}, board[i][j] = '.';
    if (c == 'X') E = {i, j}, board[i][j] = '.';
  }

  auto oob = [&](int i, int j) {
    return i < 0 || i >= h || j < 0 || j >= w;
  };

  queue<vector<pii>> q;
  q.push(P); cdist[P] = 0;

  vector<char> old(n);
  while (!q.empty()) {
    auto cur = q.front(); q.pop();

    int dist = cdist[cur];
    if (cur[0] == E) return cout << dist << '\n', void();
    if (dist == l) continue;

    // Temporarily mark the board with players
    for (int p = 0; p < n; ++p) {
      int i, j; tie(i, j) = cur[p];
      old[p] = board[i][j];
      board[i][j] = p + '1';
    }

    for (int p = 0; p < n; ++p) {
      for (int k = 0; k < 4; ++k) {
        int ci, cj; tie(ci, cj) = cur[p];
        int ni = ci + dx[k], nj = cj + dy[k];
        while (!oob(ni, nj) && board[ni][nj] == '.') {
          ci = ni, cj = nj;
          ni += dx[k], nj += dy[k];
        }

        auto next = cur;
        next[p] = {ci, cj};
        if (!cdist.count(next)) {
          cdist[next] = dist + 1;
          q.push(next);
        }
      }
    }

    for (int p = 0; p < n; ++p) {
      int i, j; tie(i, j) = cur[p];
      board[i][j] = old[p];
    }
  }

  cout << "NO SOLUTION\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
