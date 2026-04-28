#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, ans = 0; cin >> N;
  if (N & 1) {
    for (ll q = 3; q * q <= N; q += 2) {
      if (N % q == 0) {
        N -= q; ++ans;
        break;
      }
    }
    if (N & 1) return cout << "1\n", void();
  }
  assert(N % 2 == 0);
  ans += N / 2;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
