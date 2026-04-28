#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, T, K; cin >> N >> M >> T >> K;
  ll ans = 0, price = K;
  while (1) {
    if (N < M) {
      ans += N * price;
      break;
    }
    ans += M * price;
    price -= T; N -= M;
    if (price <= 0) break;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
