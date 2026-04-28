#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 12;
char board[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) {
    for (int j = m - 1; j >= 0; j--) cout << board[i][j];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
