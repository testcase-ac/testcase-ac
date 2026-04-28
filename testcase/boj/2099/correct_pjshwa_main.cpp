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

int main() {
  fast_io();

  ll n, k, m;
  int a1, a2;
  cin >> n >> k >> m;

  matrix ans = matrix(n, vector<ll>(n));
  matrix a = matrix(n, vector<ll>(n));

  for (int i = 0; i < n; i++) ans[i][i] = 1;

  for (int i = 1; i <= n; i++) {
    cin >> a1 >> a2;
    a[i - 1][a1 - 1] = 1;
    a[i - 1][a2 - 1] = 1;
  }

  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  while (m--) {
    cin >> a1 >> a2;
    cout << (ans[a1 - 1][a2 - 1] ? "death" : "life") << '\n';
  }
}
