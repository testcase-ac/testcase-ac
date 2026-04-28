#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, L; cin >> N >> L;

  vector<pll> A;
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ll k, t; cin >> k >> t;
    if (t <= 5) ans += t;
    else A.push_back({k, t});
  }

  sort(A.begin(), A.end(), greater<>());

  ll u = 0;
  for (auto [k, t] : A) {
    if (u + k * t > L) {
      ll dif = u + k * t - L;
      ans += dif; u -= dif;
    }
    ans += t; u += k * (t - 5);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
