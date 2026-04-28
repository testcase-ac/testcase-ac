#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const ll mod = 1e9 + 7;
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

matrix maps[100];
int main() {
  fast_io();

  ll t, n, d, mi, a, b, c;
  cin >> t >> n >> d;

  for (int i = 0; i < t; i++) {
    cin >> mi;
    matrix m = matrix(n, vector<ll>(n));
    while (mi--) {
      cin >> a >> b >> c;
      m[a - 1][b - 1] = c;
    }
    maps[i] = m;
  }

  matrix ans = matrix(n, vector<ll>(n));
  matrix cyc = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) ans[i][i] = cyc[i][i] = 1;
  for (int i = 0; i < t; i++) cyc = cyc * maps[i];

  ll k = d / t;
  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * cyc;
    cyc = cyc * cyc;
    k /= 2;
  }

  for (int i = 0; i < d % t; i++) ans = ans * maps[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << ans[i][j] << ' ';
    cout << '\n';
  }
}
