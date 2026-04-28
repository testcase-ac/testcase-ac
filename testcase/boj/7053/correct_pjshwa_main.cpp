#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const double EPS = 1e-9;
const int N = 751;

int gauss (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }

    for (int i=0; i<m; ++i) ans[i] = 0;
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (sum != a[i][m]) return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(2 * n);
  for (int i = 0; i < 2 * n; i++) cin >> a[i];

  vector<bitset<N>> v(n);
  bitset<N> ans;
  for (int i = 0; i < n; i++) {
    for (int j = n - 1; j >= 0; j--) v[i][n - 1 - j] = a[i + j];
    v[i][n] = a[i + n];
  }

  int res = gauss(v, n, n, ans);
  if (res) for (int i = 0; i < n; i++) cout << ans[i] << " ";
  else cout << -1;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
