#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, ans = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];
  if (N <= 2) {
    for (int j = 1; j < M - 1; ++j) {
      int ok = 0;
      for (int i = 0; i < N; ++i) {
        if (board[i][j] == '#') ok = 1;
      }
      ans += 1 - ok;
    }
  }
  else if (M <= 2) {
    for (int i = 1; i < N - 1; ++i) {
      int ok = 0;
      for (int j = 0; j < M; ++j) {
        if (board[i][j] == '#') ok = 1;
      }
      ans += 1 - ok;
    }
  }
  else {
    for (int i = 1; i < N - 1; ++i) for (int j = 1; j < M - 1; ++j) {
      if (board[i][j] == '#') continue;
      ++ans; board[i][j] = '#';
    }
  
    int border = 0;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
      if (board[i][j] == '.') continue;

      // skip if corner
      if (i == 0 && j == 0) continue;
      if (i == 0 && j == M - 1) continue;
      if (i == N - 1 && j == 0) continue;
      if (i == N - 1 && j == M - 1) continue;

      if (i == 0 || i == N - 1 || j == 0 || j == M - 1) ++border;
    }
    if (border == 0) ++ans;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
