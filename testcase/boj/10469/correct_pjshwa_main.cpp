#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 8;
char board[MAX + 1][MAX + 1];

void solve() {
  int n = 8, c = 0;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pii> queens;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '.') continue;
    for (auto& [qx, qy] : queens) {
      if (i == qx || j == qy || abs(i - qx) == abs(j - qy)) return cout << "invalid\n", void();
    }
    queens.push_back({i, j});
  }

  if (queens.size() == n) cout << "valid\n";
  else cout << "invalid\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
