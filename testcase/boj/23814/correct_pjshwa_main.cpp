#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll d, n, m, k;
  cin >> d >> n >> m >> k;

  ll v = n / d + m / d + k / d, ans = k;
  ll nf = (d - n % d) % d, mf = (d - m % d) % d;
  if (nf <= k) {
    ll c = (n + nf) / d + m / d + (k - nf) / d;
    if (c > v) {
      v = c;
      ans = k - nf;
    }
    else if (c == v) ans = max(ans, k - nf);
  }
  if (mf <= k) {
    ll c = n / d + (m + mf) / d + (k - mf) / d;
    if (c > v) {
      v = c;
      ans = k - mf;
    }
    else if (c == v) ans = max(ans, k - mf);
  }
  if (nf + mf <= k) {
    ll c = (n + nf) / d + (m + mf) / d + (k - nf - mf) / d;
    if (c > v) {
      v = c;
      ans = k - nf - mf;
    }
    else if (c == v) ans = max(ans, k - nf - mf);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
