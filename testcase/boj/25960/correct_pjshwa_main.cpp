#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx_4[] = {0, 1, 0, -1}, dy_4[] = {1, 0, -1, 0};
const int dw_4[] = {1, 1, -1, -1}, dz_4[] = {1, -1, -1, 1};
const int dk_8[] = {1, 2, 2, 1, -1, -2, -2, -1}, dl_8[] = {2, 1, -1, -2, -2, -1, 1, 2};

string board[MAXN][MAXN];
int cdist[MAXN][MAXN];
vector<tuple<int, int, int>> adj[MAXN][MAXN];

void solve() {
  int N; cin >> N;

  memset(cdist, 0x3f, sizeof(cdist));
  int si, sj, ei, ej;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cin >> board[i][j];
    if (board[i][j] == "P") si = i, sj = j, board[i][j] = "0";
    if (board[i][j] == "K") ei = i, ej = j;
  }

  auto oob = [&](int i, int j) { return i < 0 || i >= N || j < 0 || j >= N; };

  using T = tuple<int, int, int>;
  priority_queue<T, vector<T>, greater<T>> q;

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[i][j] == "Q") {
      for (int d = 0; d < 4; ++d) {
        int ni = i + dx_4[d], nj = j + dy_4[d], c = 1;
        while (!oob(ni, nj) && board[ni][nj] == "0") {
          ni += dx_4[d], nj += dy_4[d], ++c;
        }
        if (!oob(ni, nj)) {
          adj[i][j].emplace_back(ni, nj, c);
        }
      }
      for (int d = 0; d < 4; ++d) {
        int ni = i + dw_4[d], nj = j + dz_4[d], c = 1;
        while (!oob(ni, nj) && board[ni][nj] == "0") {
          ni += dw_4[d], nj += dz_4[d], ++c;
        }
        if (!oob(ni, nj)) {
          adj[i][j].emplace_back(ni, nj, c);
        }
      }
    }

    if (board[i][j] == "R") {
      for (int d = 0; d < 4; ++d) {
        int ni = i + dx_4[d], nj = j + dy_4[d], c = 1;
        while (!oob(ni, nj) && board[ni][nj] == "0") {
          ni += dx_4[d], nj += dy_4[d], ++c;
        }
        if (!oob(ni, nj)) {
          adj[i][j].emplace_back(ni, nj, c);
        }
      }
    }

    if (board[i][j] == "B") {
      for (int d = 0; d < 4; ++d) {
        int ni = i + dw_4[d], nj = j + dz_4[d], c = 1;
        while (!oob(ni, nj) && board[ni][nj] == "0") {
          ni += dw_4[d], nj += dz_4[d], ++c;
        }
        if (!oob(ni, nj)) {
          adj[i][j].emplace_back(ni, nj, c);
        }
      }
    }

    if (board[i][j] == "N") {
      for (int d = 0; d < 8; ++d) {
        int ni = i + dk_8[d], nj = j + dl_8[d];
        if (!oob(ni, nj) && board[ni][nj] != "0") {
          adj[i][j].emplace_back(ni, nj, 2);
        }
      }
    }

    // board[i][j] == "P"
    if (i == si && j == sj) {
      for (int d = 0; d < 4; ++d) {
        int ni = i + dx_4[d], nj = j + dy_4[d];
        if (!oob(ni, nj) && board[ni][nj] != "0") {
          adj[i][j].emplace_back(ni, nj, 1);
        }
      }
      for (int d = 0; d < 4; ++d) {
        int ni = i + dw_4[d], nj = j + dz_4[d];
        if (!oob(ni, nj) && board[ni][nj] != "0") {
          adj[i][j].emplace_back(ni, nj, 1);
        }
      }

      cdist[i][j] = 0;
      q.emplace(0, i, j);
    }
  }

  while (!q.empty()) {
    auto [d, i, j] = q.top(); q.pop();
    if (cdist[i][j] < d) continue;

    for (auto [ni, nj, c] : adj[i][j]) {
      if (cdist[ni][nj] > d + c) {
        cdist[ni][nj] = d + c;
        q.emplace(d + c, ni, nj);
      }
    }
  }

  int ans = cdist[ei][ej];
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
