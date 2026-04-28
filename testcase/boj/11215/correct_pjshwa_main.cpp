#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  int x = 0;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    for (int j = 0; j < M; j++) {
      board[i][j] = S[j] == 'X';
      x += board[i][j];
    }
  }

  if (x == 0) return cout << "possible\n", void();
  if (N == 1) {
    if (M < 3) cout << "impossible\n";
    else {
      for (int j = 0; j < M - 3; j++) {
        if (board[0][j] == 0) continue;
        for (int k = 0; k < 4; k++) board[0][j + k] ^= 1;
      }

      for (int j = 0; j < M; j++) {
        if (board[0][j] == 1) return cout << "impossible\n", void();
      }
      cout << "possible\n";
    }
  }
  else if (M == 1) {
    if (N < 3) cout << "impossible\n";
    else {
      for (int i = 0; i < N - 3; i++) {
        if (board[i][0] == 0) continue;
        for (int k = 0; k < 4; k++) board[i + k][0] ^= 1;
      }

      for (int i = 0; i < N; i++) {
        if (board[i][0] == 1) return cout << "impossible\n", void();
      }
      cout << "possible\n";
    }
  }
  else if (N == 2 && M == 2) {
    if (x == 4) cout << "possible\n";
    else cout << "impossible\n";
  }
  else {
    if (x % 2 == 0) cout << "possible\n";
    else cout << "impossible\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
