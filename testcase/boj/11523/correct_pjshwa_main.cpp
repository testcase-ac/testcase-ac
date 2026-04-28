#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

void solve() {
  int tc, n;
  cin >> tc >> n;
  cout << tc << ' ';

  ll ans = 0;
  for (int c2 = n / 2; c2 >= 0; c2--) {
    int c1 = n - 2 * c2;
    if (c2 < c1) break;

    if (c1 & 1) continue;
    if (c2 & 1) continue;

    int v1 = c1 / 2, v2 = c2 / 2;
    ll v = C(v1 + v2, v1);
    ans += v * v;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
