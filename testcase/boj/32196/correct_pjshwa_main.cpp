#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, K, X, Y; cin >> N >> M >> K >> X >> Y;

  vector<ll> A;
  for (int i = 0; i < N; ++i) {
    ll a, b; cin >> a >> b;
    ll bonus = a * X - b * Y;
    A.push_back(bonus);
  }
  sort(A.begin(), A.end(), greater<>());

  ll ans = K * (X + Y);
  while (M--) {
    ans += A.back();
    A.pop_back();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
