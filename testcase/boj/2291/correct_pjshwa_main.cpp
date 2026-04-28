#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
ll d[MAX][11][MAX];

ll r(int s, int n, int m) {
  if (d[s][n][m] != -1) return d[s][n][m];

  if (n == 0) return d[s][n][m] = m == 0;
  else {
    ll res = 0;
    for (int i = s; i <= m; i++) {
      res += r(i, n - 1, m - s);
    }
    return d[s][n][m] = res;
  }
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  memset(d, -1, sizeof(d));

  int l = 1;
  while (1) {
    ll cum = 0;
    for (int i = l; i <= m; i++) {
      if (cum + r(i, n, m) < k) cum += r(i, n, m);
      else {
        cout << i << ' ';
        k -= cum;
        cum = 0;
        m -= i;
        n--;
        l = i;
        break;
      }
    }

    if (n == 0) break;
  }
  cout << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
