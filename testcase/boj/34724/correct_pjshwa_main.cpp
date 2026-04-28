#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  for (int i = 1; i < N; ++i) for (int j = 1; j < M; ++j) {
    int ok = board[i][j] == '1' && board[i - 1][j] == '1' &&
             board[i][j - 1] == '1' && board[i - 1][j - 1] == '1';
    if (ok) return cout << "1\n", void();
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
