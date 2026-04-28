#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
vector<int> order;
set<int> friends[MAX * MAX + 1];
int board[MAX][MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0, x; i < n * n; i++) {
    cin >> x;
    order.push_back(x);
    for (int j = 0, y; j < 4; j++) cin >> y, friends[x].insert(y);
  }

  for (int o : order) {
    int di, dj, fc = -1, bc = -1;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
      if (board[i][j]) continue;

      int cfc = 0, cbc = 0;
      for (int k = 0; k < 4; k++) {
        int ni = i + dx[k], nj = j + dy[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
        if (friends[o].count(board[ni][nj])) cfc++;
        if (!board[ni][nj]) cbc++;
      }

      if (cfc > fc || (cfc == fc && cbc > bc)) {
        fc = cfc, bc = cbc;
        di = i, dj = j;
      }
    }

    board[di][dj] = o;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int cfc = 0, o = board[i][j];
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
      if (friends[o].count(board[ni][nj])) cfc++;
    }

    if (cfc == 1) ans += 1;
    if (cfc == 2) ans += 10;
    if (cfc == 3) ans += 100;
    if (cfc == 4) ans += 1000;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
