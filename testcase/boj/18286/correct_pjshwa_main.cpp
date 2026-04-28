#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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
  ll n, m;
  cin >> n >> m;

  matrix ans = matrix(1 << m, vector<ll>(1 << m));
  matrix a = matrix(1 << m, vector<ll>(1 << m));

  for (int i = 0; i < (1 << m); i++) ans[i][i] = 1;
  for (int ps = 0; ps < (1 << m); ps++) for (int ns = 0; ns < (1 << m); ns++) {
    bool pstate = true;
    for (int j = 0; j < m - 1; j++) {
      if ((ps & (1 << j)) && (ns & (1 << j)) && (ps & (1 << (j + 1))) && (ns & (1 << (j + 1)))) pstate = false;
      if (!(ps & (1 << j)) && !(ns & (1 << j)) && !(ps & (1 << (j + 1))) && !(ns & (1 << (j + 1)))) pstate = false;
    }
    if (pstate) a[ps][ns] = 1;
  }

  // Exponentiation by squaring
  n--;
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }

  int res = 0;
  for (int i = 0; i < (1 << m); i++) for (int j = 0; j < (1 << m); j++) res = (res + ans[i][j]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
