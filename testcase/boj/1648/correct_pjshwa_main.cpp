#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 14, MOD = 9901;
int d[MAX][MAX][1 << MAX];
int n, m;

int r(int i, int j, int b) {
  if (i == n && j == 0) return 1;

  b &= (1 << m) - 1;
  if (d[i][j][b] != -1) return d[i][j][b];

  int ni, nj;
  if (j == m - 1) ni = i + 1, nj = 0;
  else ni = i, nj = j + 1;

  int res = 0;
  if (b & (1 << (m - 1))) {
    res = (res + r(ni, nj, b << 1)) % MOD;
  }
  else {
    if (j < m - 1 && (b & (1 << (m - 2))) == 0) {
      res = (res + r(ni, nj, (b << 1) | (1 << (m - 1)))) % MOD;
    }
    if (i < n - 1) {
      res = (res + r(ni, nj, (b << 1) | 1)) % MOD;
    }
  }

  return d[i][j][b] = res;
}

void solve() {
  cin >> n >> m;
  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
