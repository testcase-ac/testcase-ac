#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

const int mod = 1e9 + 7;
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
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n;
  cin >> n;

  matrix ans = matrix(2, vector<ll>(2));
  matrix a = matrix(2, vector<ll>(2));

  for (int i = 0; i < 2; i++) ans[i][i] = 1;
  a[0][0] = a[1][0] = a[1][1] = 1;
  a[0][1] = 2;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }

  cout << (ans[0][0] + ans[0][1]) % mod;
}
