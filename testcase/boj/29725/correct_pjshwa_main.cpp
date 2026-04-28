#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_lower(char c) {
  return 'a' <= c && c <= 'z';
}

int score(char c) {
  bool neg = is_lower(c);
  c = tolower(c);

  int ret = 0;
  if (c == 'q') ret = 9;
  else if (c == 'r') ret = 5;
  else if (c == 'b') ret = 3;
  else if (c == 'n') ret = 3;
  else if (c == 'p') ret = 1;

  return neg ? -ret : ret;
}

void solve() {
  char board[8][9];
  for (int i = 0; i < 8; ++i) cin >> board[i];

  int ans = 0;
  for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) {
    ans += score(board[i][j]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
