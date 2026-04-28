#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 1e9 + 7;
ll fac[MAXN + 1], f[MAXN + 1], g[MAXN + 1][MAXN + 1], C[MAXN + 1][MAXN + 1];

void solve() {
  int x, i; cin >> x >> i;
  cout << g[x][i] << '\n';
}

int main() {
  fast_io();

  C[0][0] = 1;
  for (int i = 1; i <= MAXN; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
  }

  fac[0] = 1;
  for (int i = 1; i <= MAXN; i++)
    fac[i] = (fac[i - 1] * i) % MOD;

  f[0] = f[1] = 1;
  for (int x = 2; x <= MAXN; ++x) {
    ll ret = 0;
    for (int i = 1; i <= x; ++i) {
      ll cur = C[x][i] * f[x - i] % MOD;
      ret = (ret + cur) % MOD;
    }
    f[x] = ret;
  }

  for (int d = 0; d <= MAXN; ++d) {
    ll back = 0;
    for (int b = 0; b <= d; ++b) {
      ll tmp = C[d][b];
      tmp = (tmp * f[b]) % MOD;
      back = (back + tmp) % MOD;
    }

    for (int i = 1; i <= MAXN; ++i) {
      int x = d + i;
      if (x > MAXN) break;

      ll front = C[x - 1][i - 1];
      front = (front * f[i - 1]) % MOD;

      g[x][i] = (front * back) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
