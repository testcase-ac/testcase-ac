#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400;
char board[MAX + 1][MAX + 1];
int s[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'X') continue;
    else s[i][j] = j == 0 ? 1 : s[i][j - 1] + 1;
  }

  int ans = 0;
  for (int w = 1; w <= m; w++) {
    for (int j = 0; j < m; j++) {
      int streak = 0, mstreak = 0;
      for (int i = 0; i < n; i++) {
        if (s[i][j] >= w) streak++;
        else mstreak = max(mstreak, streak), streak = 0;
      }
      mstreak = max(mstreak, streak);
      if (mstreak) ans = max(ans, 2 * (w + mstreak));
    }
  }

  cout << ans - 1 << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
