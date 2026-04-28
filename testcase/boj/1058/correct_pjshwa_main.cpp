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

  ll n;
  char str[51];
  cin >> n;

  matrix a = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    cin >> str;
    for (int j = 0; j < n; j++) {
      if (str[j] == 'Y') a[i][j] = 1;
    }
  }

  matrix b = a * a;
  int mv = -1;
  for (int i = 0; i < n; i++) {
    int mtv = 0;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;

      if (a[i][j] || b[i][j]) mtv++;
    }

    mv = max(mv, mtv);
  }

  cout << mv << '\n';
}
