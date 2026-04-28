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

  int t;
  cin >> t;

  while (t--) {
    ll n;
    cin >> n;

    if (n == 1) cout << 1;
    else if (n == 2) cout << 3;
    else if (n == 3) cout << 10;
    else if (n == 4) cout << 23;
    else if (n == 5) cout << 62;
    else {
      n -= 5;

      matrix ans = matrix(6, vector<ll>(6));
      matrix a = matrix(6, vector<ll>(6));

      for (int i = 0; i < 6; i++) ans[i][i] = 1;
      a[0][0] = a[1][0] = a[2][1] = a[3][2] = a[4][3] = a[5][4] = 1;
      a[0][1] = 2;
      a[0][2] = 6;
      a[0][3] = 1;
      a[0][5] = mod - 1;

      // Exponentiation by squaring
      while (n) {
        if (n & 1) ans = ans * a;
        a = a * a;
        n /= 2;
      }

      cout << (ans[0][5] + ans[0][4] + 3 * ans[0][3] + 10 * ans[0][2] + 23 * ans[0][1] + 62 * ans[0][0]) % mod;
    }
    cout << '\n';
  }
}
