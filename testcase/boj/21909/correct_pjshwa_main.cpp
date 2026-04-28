#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int d[MAX + 1], r[MAX + 1];

void solve() {
  int n;
  cin >> n;

  ll ans = 0;
  map<pii, int> t;
  t[{0, 0}] = 1;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    r[i] = (r[i - 1] + x) % 3;
    d[i] = (d[i - 1] + r[i - 1] * x) % 3;

    for (int le = 0; le < 3; le++) for (int re = 0; re < 3; re++) {
      if ((le + re) % 3 != r[i]) continue;
      int v = (le * re) % 3;
      ans += t[{le, (d[i] + 3 - v) % 3}];
    }
    t[{r[i], d[i]}]++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
