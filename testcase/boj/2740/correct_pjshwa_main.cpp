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
  int n = a.size(), m = b.size(), k = b[0].size();
  matrix c(n, vector<ll>(k));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      for (int l = 0; l < m; l++) c[i][j] = (c[i][j] + a[i][l] * b[l][j]) % mod;
    }
  }
  return c;
}

int main() {
  fast_io();

  ll n, m, k;
  cin >> n >> m;

  matrix a = matrix(n, vector<ll>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> a[i][j];
  }

  cin >> m >> k;
  matrix b = matrix(m, vector<ll>(k));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) cin >> b[i][j];
  }

  matrix c = a * b;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) cout << c[i][j] << ' ';
    cout << '\n';
  }
}
