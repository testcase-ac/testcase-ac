#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int mod = 1e9 + 7;
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

matrix id, dp[1000001];
matrix exp_sum(const matrix &a, int K) {
  if (K == 1) return dp[1] = a;

  int h = K / 2;
  matrix r = exp_sum(a, h);
  matrix e = dp[h];
  dp[K] = (K & 1) ? e * e * a : e * e;

  matrix ans = r + e * r;
  if (K & 1) ans = ans + dp[K];
  return ans;
}

int main() {
  fast_io();

  int N, M, K;
  cin >> N >> M >> K;
  id = matrix(N, vector<ll>(N));
  for (int i = 0; i < N; i++) id[i][i] = 1;

  matrix a = matrix(N, vector<ll>(N));
  while (M--) {
    int U, V;
    cin >> U >> V;
    a[U - 1][V - 1]++;
    a[V - 1][U - 1]++;
  }

  vector<int> ps, qs;
  int pc, qc;
  cin >> pc >> qc;
  ps.resize(pc);
  qs.resize(qc);
  for (int i = 0; i < pc; i++) cin >> ps[i];
  for (int i = 0; i < qc; i++) cin >> qs[i];

  matrix am = exp_sum(a, K);
  ll c = 0;
  for (int pi : ps) for (int qi : qs) c = (c + am[pi - 1][qi - 1]) % mod;
  cout << c;
}
