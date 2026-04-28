#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, mod, p;

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

void solve() {
  matrix ans = matrix(n, vector<ll>(n));
  matrix a = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  for (int i = 0; i < n; i++) ans[i][i] = 1;

  // Exponentiation by squaring
  while (p) {
    if (p & 1) ans = ans * a;
    a = a * a;
    p /= 2;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << (ans[i][j] % mod) << " ";
    cout << "\n";
  }
  cout << "\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> mod >> p;
    if (n == 0 && mod == 0 && p == 0) break;
    solve();
  }
}
