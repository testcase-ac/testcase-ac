#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pll> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].second;
  for (int i = 0; i < N; i++) cin >> A[i].first;
  sort(A.begin(), A.end());

  ll ans = 0;
  auto& [u, v] = A[0];
  if (v < u) {
    ll c = (u - v - 1) / 30 + 1;
    ans += c; v += c * 30;
  }
  for (int i = 1; i < N; i++) {
    auto& [u, v] = A[i];
    auto& [pu, pv] = A[i - 1];

    ll l = max(pv, u);
    if (v < l) {
      ll c = (l - v - 1) / 30 + 1;
      ans += c; v += c * 30;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
