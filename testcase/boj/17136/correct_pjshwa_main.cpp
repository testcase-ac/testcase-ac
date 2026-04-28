#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int board[10][10];
int scnt, ans = INF;
int s[6] = {0, 5, 5, 5, 5, 5};

bool can_cover(int x, int y, int z) {
  for (int i = x; i < x + z; i++) for (int j = y; j < y + z; j++) {
    if (i >= 10 || j >= 10 || board[i][j] == 0) return false;
  }
  return true;
}

void cover(int x, int y, int z) {
  for (int i = x; i < x + z; i++) for (int j = y; j < y + z; j++) board[i][j] = 0;
}

void uncover(int x, int y, int z) {
  for (int i = x; i < x + z; i++) for (int j = y; j < y + z; j++) board[i][j] = 1;
}

void dfs(int i, int j) {
  if (i == 10 && j == 0) {
    ans = min(ans, scnt);
    return;
  }

  if (board[i][j] == 1) {
    for (int z = 1; z <= 5; z++) {
      if (s[z] && can_cover(i, j, z)) {
        scnt++;
        s[z]--;
        cover(i, j, z);
        j == 9 ? dfs(i + 1, 0) : dfs(i, j + 1);
        scnt--;
        s[z]++;
        uncover(i, j, z);
      }
    }
  }
  else j == 9 ? dfs(i + 1, 0) : dfs(i, j + 1);
}

void solve() {
  for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) cin >> board[i][j];
  dfs(0, 0);

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
