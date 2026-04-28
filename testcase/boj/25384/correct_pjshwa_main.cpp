#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000, MOD = 998244353;
ll d[MAX][MAX], a[MAX][MAX], inv[MAX + 1], C[MAX + 1], X[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> C[i];
    if (inv[C[i]]) {
      if (inv[C[i]] + 1 == i) return cout << "0\n", void();
      X[i] = inv[C[i]];
    }
    inv[C[i]] = i;
  }
  if (N == 1) return cout << "1\n", void();

  d[1][1] = 1;
  for (int c = 2; c < N; c++) {
    for (int i = 1; i < c; i++) {
      a[i][c] = (d[i][c - 1] - d[i][X[c + 1]] + MOD - d[i - 1][c - 1] + MOD + d[i - 1][X[c + 1]]) % MOD;
      d[i][c] = (d[i][c - 1] + d[i - 1][c] - d[i - 1][c - 1] + MOD + a[i][c]) % MOD;
    }
    for (int j = 1; j < c; j++) {
      a[c][j] = (d[c - 1][j] - d[X[c + 1]][j] + MOD - d[c - 1][j - 1] + MOD + d[X[c + 1]][j - 1]) % MOD;
      d[c][j] = (d[c - 1][j] + d[c][j - 1] - d[c - 1][j - 1] + MOD + a[c][j]) % MOD;
    }
    a[c][c] = (d[c - 1][c - 1] - d[X[c + 1]][c - 1] + MOD - d[c - 1][X[c + 1]] + MOD + d[X[c + 1]][X[c + 1]]) % MOD;
    d[c][c] = (d[c - 1][c] + d[c][c - 1] - d[c - 1][c - 1] + MOD + a[c][c]) % MOD;
  }

  cout << d[N - 1][N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
