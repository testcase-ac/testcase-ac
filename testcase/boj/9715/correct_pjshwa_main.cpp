#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX + 10][MAX + 10];

void solve() {
  int n, m;
  cin >> n >> m;

  memset(board, 0, sizeof(board));
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++) board[i][j] = s[j - 1] - '0';
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    if (board[i][j] == 0) continue;

    ans += 2;
    for (int k = 0; k < 4; k++) {
      int x = i + dx[k], y = j + dy[k];
      ans += max(0, board[i][j] - board[x][y]);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
