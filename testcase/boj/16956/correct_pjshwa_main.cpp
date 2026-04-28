#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];

void solve() {
  int R, C;
  cin >> R >> C;
  for (int i = 0; i < R; i++) cin >> board[i];
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (board[i][j] == '.') board[i][j] = 'D';
  }

  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (board[i][j] != 'W') continue;
    for (int k = 0; k < 4; k++) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 0 || x >= R || y < 0 || y >= C) continue;
      if (board[x][y] == 'S') return cout << "0\n", void();
    }
  }

  cout << "1\n";
  for (int i = 0; i < R; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
