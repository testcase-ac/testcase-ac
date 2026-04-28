#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int TYPE1 = 1, TYPE2 = 2, TYPE3 = 3, TYPEFIX = 100;
int board[MAX][MAX];
int vis[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  queue<tuple<int, int, int>> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == TYPE1) vis[i][j] = TYPE1, q.push(make_tuple(i, j, TYPE1));
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == TYPE2) vis[i][j] = TYPE2, q.push(make_tuple(i, j, TYPE2));
  }

  while (!q.empty()) {
    auto [i, j, t] = q.front();
    q.pop();

    if (vis[i][j] == TYPE3) {
      board[i][j] = TYPE3;
      continue;
    }

    vis[i][j] = TYPEFIX;
    board[i][j] = t;

    if (i > 0 && board[i - 1][j] != -1 && !vis[i - 1][j]) {
      vis[i - 1][j] = t;
      q.push(make_tuple(i - 1, j, t));
    }
    if (i < n - 1 && board[i + 1][j] != -1 && !vis[i + 1][j]) {
      vis[i + 1][j] = t;
      q.push(make_tuple(i + 1, j, t));
    }
    if (j > 0 && board[i][j - 1] != -1 && !vis[i][j - 1]) {
      vis[i][j - 1] = t;
      q.push(make_tuple(i, j - 1, t));
    }
    if (j < m - 1 && board[i][j + 1] != -1 && !vis[i][j + 1]) {
      vis[i][j + 1] = t;
      q.push(make_tuple(i, j + 1, t));
    }

    if (t == TYPE2) {
      if (i > 0 && board[i - 1][j] != -1 && vis[i - 1][j] == TYPE1) vis[i - 1][j] = TYPE3;
      if (i < n - 1 && board[i + 1][j] != -1 && vis[i + 1][j] == TYPE1) vis[i + 1][j] = TYPE3;
      if (j > 0 && board[i][j - 1] != -1 && vis[i][j - 1] == TYPE1) vis[i][j - 1] = TYPE3;
      if (j < m - 1 && board[i][j + 1] != -1 && vis[i][j + 1] == TYPE1) vis[i][j + 1] = TYPE3;
    }
  }

  int ans1 = 0, ans2 = 0, ans3 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == TYPE1) ans1++;
      if (board[i][j] == TYPE2) ans2++;
      if (board[i][j] == TYPE3) ans3++;
    }
  }
  cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
