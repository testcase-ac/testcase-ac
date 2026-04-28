#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int board[3][3], oboard[3][3];

void solve() {
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    string s;
    cin >> s;
    oboard[i][j] = s == "T";
  }

  int ans = 9;
  for (int state = 0; state < (1 << 8); state++) {
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) board[i][j] = oboard[i][j];

    for (int i = 0; i < 3; i++) {
      if (state & (1 << i)) {
        for (int j = 0; j < 3; j++) board[i][j] ^= 1;
      }
    }

    for (int j = 0; j < 3; j++) {
      if (state & (1 << (3 + j))) {
        for (int i = 0; i < 3; i++) board[i][j] ^= 1;
      }
    }

    if (state & (1 << 6)) for (int i = 0; i < 3; i++) board[i][i] ^= 1;
    if (state & (1 << 7)) for (int i = 0; i < 3; i++) board[i][2 - i] ^= 1;

    int c = 0;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) c += board[i][j];
    if (c == 0 || c == 9) ans = min(ans, __builtin_popcount(state));
  }

  if (ans == 9) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
