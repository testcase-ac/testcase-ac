#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
  }
  return c;
}

void solve() {
  ll N, M;
  cin >> N >> M;

  int t[6] = {0};
  while (M--) {
    int x;
    cin >> x;
    t[x]++;
  }

  ll d[6] = {0}; d[0] = 1;
  for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++) d[i] = (d[i] + d[i - j] * t[j]) % MOD;
  }
  if (N <= 5) return cout << d[N] << '\n', void();

  matrix a = matrix(5, vector<ll>(5, 0));
  matrix ans = matrix(5, vector<ll>(5, 0));
  for (int i = 0; i < 5; i++) {
    ans[i][i] = 1;
    a[0][i] = t[i + 1];
    if (i) a[i][i - 1] = 1;
  }

  N -= 5;
  while (N) {
    if (N & 1) ans = ans * a;
    a = a * a;
    N >>= 1;
  }

  ll res = 0;
  for (int i = 0; i < 5; i++) res = (res + d[5 - i] * ans[0][i]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
