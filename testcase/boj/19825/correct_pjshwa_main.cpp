#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e7;
ll a[MAX];
unsigned int b[MAX];

void solve() {
  ll n, l, r;
  unsigned int x, y, z, b1, b2;
  cin >> n >> l >> r >> x >> y >> z >> b1 >> b2;

  b[0] = b1, b[1] = b2;
  for (int i = 2; i < n; i++) b[i] = b[i - 2] * x + b[i - 1] * y + z;
  for (int i = 0; i < n; i++) a[i] = b[i] % (r - l + 1) + l;

  ll ans = 5e18, minx = 5e18, maxx = -5e18;
  for (int i = 0; i < n; i++) {
    if (minx < a[i]) ans = min(ans, minx * a[i]);
    minx = min(minx, a[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    if (maxx > a[i]) ans = min(ans, maxx * a[i]);
    maxx = max(maxx, a[i]);
  }

  if (ans == 5e18) cout << "IMPOSSIBLE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
