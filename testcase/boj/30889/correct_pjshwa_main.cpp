#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  char board[10][21]{};
  for (int i = 0; i < 10; ++i) for (int j = 0; j < 20; ++j) board[i][j] = '.';

  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    int r = S[0] - 'A';
    int c = stoi(S.substr(1)) - 1;
    board[r][c] = 'o';
  }

  for (int i = 0; i < 10; ++i) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
