#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll mod;

matrix operator + (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = (a[i][j] + b[i][j]) % mod;
    }
  }
  return c;
}

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
    }
  }
  return c;
}

matrix id;
matrix exp_sum(const matrix &a, ll K) {
  if (K == 1) return a;

  ll h = K / 2;
  matrix r = exp_sum(a, h), q = a;

  matrix e = id;
  while (h) {
    if (h & 1) e = e * q;
    q = q * q;
    h >>= 1;
  }
  matrix ans = r + e * r;
  if (K & 1) ans = ans + (e * e * a);
  return ans;
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k >> mod;

  matrix a = matrix(n, vector<ll>(n));
  id = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) id[i][i] = 1;

  char str[36];
  for (int i = 0; i < n; i++) {
    cin >> str;
    for (int j = 0; j < n; j++) a[i][j] = str[j] == 'Y';
  }

  ll ans = 0;
  matrix am = exp_sum(a, k - 1);
  for (int i = 0; i < n; i++) ans = (ans + am[i][i]) % mod;

  cout << ans << '\n';
}
