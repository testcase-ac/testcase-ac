#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int mod = 1e3;
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

void print_matrix(const matrix &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << a[i][j] % mod << ' ';
    cout << '\n';
  }
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

  ll N, K;
  cin >> N >> K;
  matrix a = matrix(N, vector<ll>(N));
  id = matrix(N, vector<ll>(N));
  for (int i = 0; i < N; i++) id[i][i] = 1;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> a[i][j];

  print_matrix(exp_sum(a, K));
}
