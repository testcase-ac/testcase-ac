#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];
bool flag[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int ans = 0;
  bool flag = false;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] != '.') ans++, flag = !flag;
    else if (flag) ans += 2;
  }

  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
