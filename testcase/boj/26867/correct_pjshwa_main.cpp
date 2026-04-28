#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MOD = 998244353;
char board[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];

  ll ans = 1;
  for (int i = 0; i < N; ++i) {
    int sj = 0;
    while (sj < N) {
      while (sj < N && board[i][sj] != '?') ++sj;

      int ej = sj;
      while (ej < N && board[i][ej] == '?') ++ej;

      int ok1 = sj > 0 && board[i][sj - 1] == '#';
      int ok2 = ej < N && board[i][ej] == '#';
      if (ok1 && ok2) return cout << "0\n", void();
      if (!ok1 && !ok2) ans = (ans * (ej - sj + 1)) % MOD;
      sj = ej;
    }
  }
  for (int j = 0; j < N; ++j) {
    int si = 0;
    while (si < N) {
      while (si < N && board[si][j] != '?') ++si;

      int ei = si;
      while (ei < N && board[ei][j] == '?') ++ei;

      int ok1 = si > 0 && board[si - 1][j] == '#';
      int ok2 = ei < N && board[ei][j] == '#';
      if (ok1 && ok2) return cout << "0\n", void();
      if (!ok1 && !ok2) ans = (ans * (ei - si + 1)) % MOD;
      si = ei;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
