#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 11;
ll d[MAX][MAX][1 << MAX];
int n, m;

ll r(int i, int j, int b) {
  if (i == n && j == 0) return 1;

  b &= (1 << m) - 1;
  if (d[i][j][b] != -1) return d[i][j][b];

  int ni, nj;
  if (j == m - 1) ni = i + 1, nj = 0;
  else ni = i, nj = j + 1;

  ll res = 0;
  if (b & (1 << (m - 1))) {
    res += r(ni, nj, b << 1);
  }
  else {
    if (j < m - 1 && (b & (1 << (m - 2))) == 0) {
      res += r(ni, nj, (b << 1) | (1 << (m - 1)));
    }
    if (i < n - 1) {
      res += r(ni, nj, (b << 1) | 1);
    }
  }

  return d[i][j][b] = res;
}

void solve() {
  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    solve();
  }
}
