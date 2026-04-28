#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

const ll mod = 31991;
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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll d, t;
  cin >> d >> t;

  matrix ans = matrix(d, vector<ll>(d));
  matrix a = matrix(d, vector<ll>(d));

  for (int i = 0; i < d; i++) ans[i][i] = 1;

  a[0][0] = 1;
  for (int i = 1; i < d; i++) {
    a[0][i] = 1;
    a[i][i - 1] = 1;
  }

  // Exponentiation by squaring
  while (t) {
    if (t & 1) ans = ans * a;
    a = a * a;
    t /= 2;
  }

  cout << ans[0][0] << '\n';
  return 0;
}
