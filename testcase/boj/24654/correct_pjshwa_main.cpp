#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
char board[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;

  if (n & 1) {
    for (int i = 1; i < n; i += 2) {
      for (int j = 1; j <= i; j++) board[i][j] = 'B';
    }
    for (int j = 2; j < n; j += 2) {
      for (int i = 0; i < j; i++) board[i][j] = 'B';
    }
  }
  else {
    for (int i = 0; i < n; i += 2) {
      for (int j = 1; j <= i; j++) board[i][j] = 'B';
    }
    for (int j = 1; j < n; j += 2) {
      for (int i = 0; i < j; i++) board[i][j] = 'B';
    }
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] != 'B') board[i][j] = 'W';
  }

  for (int i = 0; i < n; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
