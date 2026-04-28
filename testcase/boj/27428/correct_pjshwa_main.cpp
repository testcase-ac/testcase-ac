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
  ll N, K; cin >> N >> K;

  vector<int> A(K);
  for (int& x : A) cin >> x;

  ll ans = 0;
  for (int s = 1; s < (1 << K); ++s) {
    int cnt = __builtin_popcount(s);
    int mul = (1 << (cnt - 1)) * (cnt % 2 == 0 ? -1 : 1);

    ll num = 1, ok = 1;
    for (int i = 0; i < K; ++i) {
      if (s & (1 << i)) {
        num = lcm(num, A[i]);
        if (num > N) {
          ok = 0;
          break;
        }
      }
    }
    if (ok) ans += mul * (N / num);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
