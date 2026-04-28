#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, k;
  cin >> n >> k;

  ll ans = 0, sq = min(n, (ll)sqrt(k));
  for (int i = 1; i <= sq; i++) ans += i * (k / i);

  ll last = n;
  for (int i = k / n; i < k / sq; i++) {
    ll s = k / (i + 1) + 1;
    if (s <= last) {
      ll coef = last * (last + 1) / 2 - s * (s - 1) / 2;
      ans += coef * i;
      last = s - 1;
    }
  }

  cout << n * k - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
