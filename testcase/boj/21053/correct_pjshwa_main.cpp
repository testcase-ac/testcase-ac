#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

const int MAX = 1e6, MOD = 1e9 + 7;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll acur = 0, apfv = 0, ccur = 0, ans = 0;
  for (int i = 0; i < n; i++) if (a[i] == 3) ccur++;
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) acur++;
    if (a[i] == 3) ccur--;
    if (a[i] == 2) {
      ans = (ans + (apfv + acur) * ccur) % MOD;
      apfv = (2 * apfv + acur) % MOD;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
