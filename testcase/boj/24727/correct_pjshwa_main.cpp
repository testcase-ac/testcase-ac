#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int board[MAX][MAX];

void solve() {
  int n, c, e;
  cin >> n >> c >> e;

  for (int d = 0; d <= 2 * n; d++) {
    for (int i = 0; i < n; i++) {
      if (d - i < 0 || d - i >= n) continue;
      if (c == 0) break;
      board[i][d - i] = 1, c--;
    }
    if (c == 0) break;
  }

  for (int d = 2 * n; d >= 0; d--) {
    for (int i = n - 1; i >= 0; i--) {
      if (d - i < 0 || d - i >= n) continue;
      if (e == 0) break;
      if (board[i][d - i]) return cout << "-1\n", void();
      board[i][d - i] = 2, e--;
    }
    if (e == 0) break;
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] != 1) continue;

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
      if (board[ni][nj] == 2) return cout << "-1\n", void();
    }
  }

  if (e == 0) {

    cout << "1\n";

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cout << board[i][j];
      cout << '\n';
    }

  }

  else cout << "-1\n";

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
