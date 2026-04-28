#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int board[MAX][MAX];
int rpf[MAX][MAX], cpf[MAX][MAX];
bool vis[MAX][MAX];

void solve() {
  int n, m, h, w, sr, sc, fr, fc;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
  for (int i = 0; i < n; i++) {
    rpf[i][0] = board[i][0];
    for (int j = 1; j < m; j++) rpf[i][j] = rpf[i][j - 1] + board[i][j];
  }
  for (int j = 0; j < m; j++) {
    cpf[0][j] = board[0][j];
    for (int i = 1; i < n; i++) cpf[i][j] = cpf[i - 1][j] + board[i][j];
  }
  cin >> h >> w >> sr >> sc >> fr >> fc;

  queue<tii> q;
  q.push({sr - 1, sc - 1, 0});
  vis[sr - 1][sc - 1] = true;

  while (!q.empty()) {
    auto [r, c, d] = q.front();
    q.pop();

    if (r == fr - 1 && c == fc - 1) {
      cout << d << '\n';
      return;
    }

    if (r > 0 && !vis[r - 1][c]) {
      bool able = true;
      if (c == 0) able &= rpf[r - 1][w - 1] == 0;
      else able &= (rpf[r - 1][c + w - 1] == rpf[r - 1][c - 1]);
      if (able) vis[r - 1][c] = true, q.push({r - 1, c, d + 1});
    }
    if (r < n - h && !vis[r + 1][c]) {
      bool able = true;
      if (c == 0) able &= rpf[r + h][w - 1] == 0;
      else able &= (rpf[r + h][c + w - 1] == rpf[r + h][c - 1]);
      if (able) vis[r + 1][c] = true, q.push({r + 1, c, d + 1});
    }
    if (c > 0 && !vis[r][c - 1]) {
      bool able = true;
      if (r == 0) able &= cpf[h - 1][c - 1] == 0;
      else able &= (cpf[r + h - 1][c - 1] == cpf[r - 1][c - 1]);
      if (able) vis[r][c - 1] = true, q.push({r, c - 1, d + 1});
    }
    if (c < m - w && !vis[r][c + 1]) {
      bool able = true;
      if (r == 0) able &= cpf[h - 1][c + w] == 0;
      else able &= (cpf[r + h - 1][c + w] == cpf[r - 1][c + w]);
      if (able) vis[r][c + 1] = true, q.push({r, c + 1, d + 1});
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
