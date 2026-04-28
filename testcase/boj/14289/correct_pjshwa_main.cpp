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

  ll n, m, ai, bi;
  cin >> n >> m;

  matrix ans = matrix(n, vector<ll>(n));
  matrix a = matrix(n, vector<ll>(n));

  for (int i = 0; i < n; i++) ans[i][i] = 1;
  while (m--) {
    cin >> ai >> bi;
    a[ai - 1][bi - 1] = a[bi - 1][ai - 1] = 1;
  }

  ll d;
  cin >> d;

  // Exponentiation by squaring
  while (d) {
    if (d & 1) ans = ans * a;
    a = a * a;
    d /= 2;
  }

  cout << ans[0][0] << '\n';
  return 0;
}
