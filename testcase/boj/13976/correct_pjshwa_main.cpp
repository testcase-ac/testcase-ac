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

  if (n & 1) {
    cout << "0\n";
    return 0;
  }

  matrix ans = matrix(8, vector<ll>(8));
  matrix a = matrix(8, vector<ll>(8));

  for (int i = 0; i < 8; i++) ans[i][i] = 1;
  a[0][7] = 1;
  a[1][6] = 1;
  a[2][5] = 1;
  a[4][3] = 1;
  a[3][4] = a[3][7] = 1;
  a[6][1] = a[6][7] = 1;
  a[5][2] = 1;
  a[7][0] = a[7][3] = a[7][6] = 1;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }

  ll sum = 0;
  for (int i = 0; i < 7; i++) sum += ans[0][i];

  cout << sum % mod << '\n';
  return 0;
}
