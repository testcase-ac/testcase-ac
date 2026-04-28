#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  map<ll, ll> t;
  for (int i = 0; i < N; i++) {
    ll x, y; cin >> x >> y;
    y -= K * x;
    t[y]++;
  }

  ll ans = 0;
  for (auto& [_, v] : t) ans += v * (v - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
