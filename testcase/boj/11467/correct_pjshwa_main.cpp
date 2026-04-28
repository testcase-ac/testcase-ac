#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char board[MAX + 1][MAX + 1];

void solve() {
  int A, B; cin >> A >> B;
  A--; B--;

  for (int i = 0; i < 50; i++) {
    fill(board[i], board[i] + 100, '@');
    fill(board[i + 50], board[i + 50] + 100, '.');
  }

  for (int i = 0; i < 50; i++) {
    if (i & 1) continue;
    for (int j = 0; j < 100; j++) {
      if ((i + j) & 1) continue;
      if (B == 0) continue;

      B--;
      board[i][j] = '.';
    }
  }

  for (int i = 99; i >= 50; i--) {
    if (i & 1) continue;
    for (int j = 0; j < 100; j++) {
      if ((i + j) & 1) continue;
      if (A == 0) continue;

      A--;
      board[i][j] = '@';
    }
  }

  cout << "100 100\n";
  for (int i = 0; i < 100; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
