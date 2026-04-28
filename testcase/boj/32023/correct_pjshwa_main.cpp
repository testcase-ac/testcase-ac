#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, ans = 1e18; cin >> N;
  for (ll a = sqrt(N); a >= 1; --a) {
    ll b = (N - 1) / a + 1;
    assert(a <= b);
    if (b > 2 * a) break;
    ans = min(ans, a * b - N);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
