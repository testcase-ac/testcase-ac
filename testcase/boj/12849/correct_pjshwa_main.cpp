#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n;
  cin >> n;

  matrix ans = matrix(8, vector<ll>(8));
  matrix a = matrix(8, vector<ll>(8));

  for (int i = 0; i < 8; i++) ans[i][i] = 1;
  a[0][1] = a[0][2] = 1;
  a[1][0] = a[1][2] = a[1][3] = 1;
  a[2][0] = a[2][1] = a[2][3] = a[2][4] = 1;
  a[3][1] = a[3][2] = a[3][4] = a[3][5] = 1;
  a[4][2] = a[4][3] = a[4][5] = a[4][7] = 1;
  a[5][3] = a[5][4] = a[5][6] = 1;
  a[6][5] = a[6][7] = 1;
  a[7][4] = a[7][6] = 1;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }

  cout << ans[0][0] << '\n';
  return 0;
}
