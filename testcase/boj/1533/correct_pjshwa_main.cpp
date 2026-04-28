#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int mod = 1e6 + 3;
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

char omat[11][11];
int main() {
  fast_io();

  int N, S, E, T;
  cin >> N >> S >> E >> T;
  for (int i = 0; i < N; i++) cin >> omat[i];

  matrix ans = matrix(5 * N, vector<ll>(5 * N));
  matrix a = matrix(5 * N, vector<ll>(5 * N));

  for (int i = 0; i < N; i++) for (int j = 1; j <= 4; j++) a[i + N * j - N][i + N * j] = 1;

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (omat[i][j] == '0') continue;

    int o = omat[i][j] - '0';
    a[i + N * o - N][j] = 1;
  }

  for (int i = 0; i < 5 * N; i++) ans[i][i] = 1;

  // Exponentiation by squaring
  while (T) {
    if (T & 1) ans = ans * a;
    a = a * a;
    T >>= 1;
  }
  cout << ans[S - 1][E - 1];
}
