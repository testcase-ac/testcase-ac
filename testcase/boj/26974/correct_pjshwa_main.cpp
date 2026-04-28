#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300, LIM = 1e9, INF = 0x3f3f3f3f;
ll r[MAX + 1][MAX + 1], a[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) cin >> r[i][j];

  fill(a, a + N + 1, INF);
  if (N == 1) return cout << "0\n", void();

  a[1] = 0, a[2] = r[1][2];

  for (int i = 3; i <= N; i++) {
    ll dif = r[i - 1][i];

    for (ll c : {a[i - 1] - dif, a[i - 1] + dif}) {
      a[i] = c;

      bool f = true;
      for (int j = i - 1; j >= 1; j--) {
        ll pmin = INF, pmax = -INF;
        for (int k = j; k <= i; k++) pmin = min(pmin, a[k]), pmax = max(pmax, a[k]);

        if (pmax - pmin != r[j][i]) {
          f = false;
          break;
        }
      }

      if (f) break;
    }
  }

  ll rmin = INF, rmax = -INF;
  for (int i = 1; i <= N; i++) {
    rmin = min(rmin, a[i]);
    rmax = max(rmax, a[i]);
  }

  if (rmin < -LIM) {
    ll dif = -LIM - rmin;
    for (int i = 1; i <= N; i++) a[i] += dif;
  }
  else if (rmax > LIM) {
    ll dif = LIM - rmax;
    for (int i = 1; i <= N; i++) a[i] += dif;
  }

  for (int i = 1; i <= N; i++) cout << a[i] << (i == N ? '\n' : ' ');
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
