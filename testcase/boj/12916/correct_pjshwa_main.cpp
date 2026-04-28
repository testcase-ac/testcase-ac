#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
int n;
matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
  }
  return c;
}

void solve() {
  int k;
  cin >> n >> k;
  matrix ans = matrix(n, vector<ll>(n));
  matrix a = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  for (int i = 0; i < n; i++) ans[i][i] = 1;

  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  int res = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) res = (res + ans[i][j]) % MOD;
  cout << res << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
