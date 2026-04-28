#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  ll N, A, B; cin >> N >> A >> B;
  if (A > B) swap(A, B);

  ll L = lcm(A, B), use = 0;
  for (ll u = 0;; u++) {
    ll Bu = B * u;
    if (Bu >= min(L, N + 1)) break;
    use += (N - Bu) / A + 1;
  }
  cout << N - use + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
