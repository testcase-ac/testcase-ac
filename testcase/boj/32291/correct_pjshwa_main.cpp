#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N; ++N;

  vector<ll> factors{1};
  for (ll f = 2; f * f <= N; ++f) {
    if (N % f) continue;
    factors.push_back(f);
    if (f * f != N) factors.push_back(N / f);
  }
  sort(factors.begin(), factors.end());

  for (ll f : factors) {
    ll val_a = (N - 1) / f;
    ll val_b = N / f;
    if (val_a < val_b) cout << f << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
