#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

const int mod = 1e9;
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

void solve() {
  int tc;
  ll y;
  cin >> tc >> y;

  matrix ans = matrix(2, vector<ll>(2));
  matrix a = matrix(2, vector<ll>(2));
  for (int i = 0; i < 2; i++) ans[i][i] = 1;
  a[0][0] = a[0][1] = a[1][0] = 1;

  // Exponentiation by squaring
  while (y) {
    if (y & 1) ans = ans * a;
    a = a * a;
    y /= 2;
  }

  cout << tc << ' ' << ans[0][1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
